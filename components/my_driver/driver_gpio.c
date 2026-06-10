#include <stdint.h>
#include <stdio.h>
#include "driver_hw_registers_gpio.h"
#include "driver_gpio.h"


// **** Secciones del archivo:
// - Variables globales.
// - Definición de funciones para configurar GPIOs.




/**************************************************************************/
// **** Variables globales:

// Variable para definir qué GPIOs tienen lógica negativa:
uint64_t inverted_gpios = 0x00000000;
// inverted_gpios & (1UL << gpio_num) == 0	-> Lógica positiva.
// inverted_gpios & (1UL << gpio_num) == 1	-> Lógica negativa.




/**************************************************************************/
// **** Definición de funciones:

// Funciones para configurar GPIOs como salidas binarias normales:

void driver_gpio_config_out(uint8_t gpio_num, uint8_t invert_logic){
	
	if(!VALID_GPIO_OUTPUT(gpio_num)) return;
	
	
	SET_OUTPUT_ENABLE_BITS(REG_BIT_GPIO_X(gpio_num));
	
	if(invert_logic)
		SET_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
	else
		CLEAR_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
 		
	
	// Configuración del IO MUX (dehabilitación de entrada y pull mode):
 
	CLEAR_REG_BITS(
		REG_GPIO_X_IO_MUX(gpio_num), 
		REG_IO_MUX_INPUT_EN_BIT		| 
		REG_IO_MUX_PULL_UP_EN_BIT 	|  
		REG_IO_MUX_PULL_DOWN_EN_BIT
	);
	
	// Configuración de la función del GPIO y fuerza del drive:
	REG_IO_MUX_X_MCU_SEL_GPIO_FUN(gpio_num);
	
	CLEAR_REG_BITS(
		REG_GPIO_X_IO_MUX(gpio_num), REG_IO_MUX_FUN_DRV_BITS_FIELD
	);
	SET_REG_BITS(
		REG_GPIO_FUNC_X_OUT_SEL_CFG(gpio_num), REG_IO_MUX_FUN_DRV_BITS_20MA
	);
	
	
	// **** Lógica para inversión de señal:
	if(invert_logic)
		inverted_gpios |= (1UL << gpio_num);
	else
		inverted_gpios &= ~(1UL << gpio_num);
	
	return;
}

void driver_gpio_config_out_bits(uint32_t gpio_bits){
	uint8_t i;
	
	for(i = 0; i < 40; i++){
		if((gpio_bits >> i) & 1)
			driver_gpio_config_out(i, 0);
	}
	return;
}


// Funciones para configurar GPIOs como entradas binarias normales:

void driver_gpio_config_in(uint8_t gpio_num, gpio_mode_e pull_mode, uint8_t invert_logic){
	
	if(!VALID_GPIO(gpio_num)) return;
	if(
		pull_mode != INPUT_MODE 		&& 
		pull_mode != INPUT_PULLUP_MODE 	&& 
		pull_mode != INPUT_PULLDOWN_MODE
	) return;
	
	// **** Habilitación y configuración de GPIO con cierto pull mode:
	
	// Habilitación del pin como entrada:
	SET_INPUT_ENABLE_BITS(REG_BIT_GPIO_X(gpio_num));
	
	// Configuración del IO MUX (habilitación y pull mode):
	SET_REG_BITS(
		REG_GPIO_X_IO_MUX(gpio_num), REG_IO_MUX_INPUT_EN_BIT |
		(pull_mode == INPUT_MODE 		? 0x00 :
		 pull_mode == INPUT_PULLUP_MODE ? REG_IO_MUX_PULL_UP_EN_BIT :
		 REG_IO_MUX_PULL_DOWN_EN_BIT)
	);
 
	CLEAR_REG_BITS(
		REG_GPIO_X_IO_MUX(gpio_num),
		(pull_mode == INPUT_MODE 		? REG_IO_MUX_PULL_UP_EN_BIT |  REG_IO_MUX_PULL_DOWN_EN_BIT:
		 pull_mode == INPUT_PULLUP_MODE ? REG_IO_MUX_PULL_DOWN_EN_BIT :
		 REG_IO_MUX_PULL_UP_EN_BIT)
	);
	
	// Configuración de la función del GPIO y fuerza del drive:
	REG_IO_MUX_X_MCU_SEL_GPIO_FUN(gpio_num);
	CLEAR_REG_BITS(
		REG_GPIO_X_IO_MUX(gpio_num), REG_IO_MUX_FUN_DRV_BITS
	);
	
	
	// **** Lógica para inversión de señal:
	if(invert_logic)
		inverted_gpios |= (1UL << gpio_num);
	else
		inverted_gpios &= ~(1UL << gpio_num);
	
	
	// **** Recursos para debuggeo:
	
	/*
	printf("GPIO %d configured as input\n", gpio_num);
	
	printf(
		"IO_MUX_%d (%p) state: 0x%x\n\n", 
		gpio_num,
		REG_GPIO_X_IO_MUX(gpio_num),
		(unsigned int)READ_REG(REG_GPIO_X_IO_MUX(gpio_num))
	);
	*/
	
	return;
}

void driver_gpio_config_in_bits(uint32_t gpio_bits, gpio_mode_e pull_mode){
	uint8_t i;
	
	for(i = 0; i < 40; i++){
		if((gpio_bits >> i) & 1)
			driver_gpio_config_in(i, pull_mode, 0);
	}
	return;
}


// Funciones para leer y escribir en pines GPIO compatibles:
uint8_t driver_gpio_read(uint8_t gpio_num){
	if(READ_REG_BIT(REG_GPIO_ENABLE, REG_BIT_GPIO_X(gpio_num)) == GPIO_INPUT){
		// Bit leído == 0 (Entrada):
		return READ_INPUT_PIN(gpio_num) ^ ((inverted_gpios >> gpio_num) & 1);
	}
	else{
		// Bit leído == 1 (Salida):
		return READ_OUTPUT_PIN(gpio_num) ^ ((inverted_gpios >> gpio_num) & 1);
	}	
}

void driver_gpio_write(uint8_t gpio_num, uint8_t state){
	// Si el GPIO está configurado como entrada en el registro de habilitación,
	// no escribe nada y retorna:
	if(READ_REG_BIT(REG_GPIO_ENABLE, REG_BIT_GPIO_X(gpio_num)) == GPIO_INPUT)
		return;
	
	// El GPIO está configurado como salida y se escribe el estado deseado:
	if(state ^ ((inverted_gpios >> gpio_num) & 1))
		SET_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
	else
		CLEAR_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
		
	return;
}

uint8_t driver_gpio_toggle(uint8_t gpio_num){
	// Si el GPIO está configurado como salida en el registro de habilitación,
	// escribe el valor opuesto al estado actual y lo retorna:
	if(READ_REG_BIT(REG_GPIO_ENABLE, REG_BIT_GPIO_X(gpio_num)) == GPIO_OUTPUT){
		TOGGLE_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
		return READ_OUTPUT_PIN(gpio_num) ^ ((inverted_gpios >> gpio_num) & 1);
	}
	return 0;
}

uint8_t driver_has_inverted_logic(uint8_t gpio_num){
	return (inverted_gpios >> gpio_num) & 1;
}

