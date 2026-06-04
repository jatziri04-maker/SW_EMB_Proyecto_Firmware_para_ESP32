#include <stdint.h>
#include <stdio.h>
#include "hw_registers_gpio.h"
#include "gpio_2026.h"




// Funciones para configurar GPIOs como salidas binarias normales:

void gpio_config_out(uint8_t gpio_num, uint8_t invert_logic){
	if(VALID_GPIO_OUTPUT(gpio_num)){
		SET_OUTPUT_ENABLE_BITS(REG_BIT_GPIO_X(gpio_num));
		CLEAR_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
	}
	return;
}

void gpio_config_out_bits(uint32_t gpio_bits){
	uint8_t i;
	
	for(i = 0; i < 40; i++){
		if(((gpio_bits >> i) & 1) && !VALID_GPIO_OUTPUT(i))
			return;
	}
	
	SET_OUTPUT_ENABLE_BITS(gpio_bits);
	CLEAR_OUTPUT_BITS(gpio_bits);
	
	return;
}


// Funciones para configurar GPIOs como entradas binarias normales:

void gpio_config_in(uint8_t gpio_num, uint8_t pull_mode, uint8_t invert_logic){
	if(!VALID_GPIO(gpio_num)) return;
	
	
	if(invert_logic){
		CLEAR_REG_BITS(REG_GPIO_FUNC_X_IN_SEL_CFG(gpio_num), 0xFFFFFFFF);
		SET_REG_BITS(REG_GPIO_FUNC_X_IN_SEL_CFG(gpio_num), gpio_num);
		
		SET_REG_BITS(REG_GPIO_FUNC_X_IN_SEL_CFG(gpio_num), FUNC_IN_INV_SEL_BIT);
		
		SET_REG_BITS(REG_GPIO_FUNC_X_IN_SEL_CFG(gpio_num), SIG_IN_SEL_BIT);
		
		printf(
			"GPIO_FUNC_%d_IN_SEL_CFG (%p) state: 0x%x\n\n", 
			gpio_num,
			REG_GPIO_FUNC_X_IN_SEL_CFG(gpio_num),
			(unsigned int)READ_REG(REG_GPIO_FUNC_X_IN_SEL_CFG(gpio_num))
		);
	}
	
	//printf("GPIO %d configured as input\n", gpio_num);

	SET_INPUT_ENABLE_BITS(REG_BIT_GPIO_X(gpio_num));

	SET_REG_BITS(
		REG_GPIO_X_IO_MUX(gpio_num), REG_IO_MUX_INPUT_EN_BIT |
		(pull_mode == INPUT_NO_PULL_MODE 	? 0x00 :
		 pull_mode == INPUT_PULLUP_MODE 	? REG_IO_MUX_PULL_UP_EN_BIT :
		 REG_IO_MUX_PULL_DOWN_EN_BIT)
	);
 
	CLEAR_REG_BITS(
		REG_GPIO_X_IO_MUX(gpio_num),
		(pull_mode == INPUT_NO_PULL_MODE 	? REG_IO_MUX_PULL_UP_EN_BIT |  REG_IO_MUX_PULL_DOWN_EN_BIT:
		 pull_mode == INPUT_PULLUP_MODE 	? REG_IO_MUX_PULL_DOWN_EN_BIT :
		 REG_IO_MUX_PULL_UP_EN_BIT)
	);

	REG_IO_MUX_X_MCU_SEL_GPIO_FUN(gpio_num);
	CLEAR_REG_BITS(REG_GPIO_X_IO_MUX(gpio_num), REG_IO_MUX_FUN_DRV_BITS);
	
	/*
	printf(
		"IO_MUX_%d (%p) state: 0x%x\n\n", 
		gpio_num,
		REG_GPIO_X_IO_MUX(gpio_num),
		(unsigned int)READ_REG(REG_GPIO_X_IO_MUX(gpio_num))
	);
	*/
	
	return;
}

void gpio_config_in_bits(uint32_t gpio_bits, uint8_t pull_mode){
	uint8_t i;
	
	for(i = 0; i < 40; i++){
		if(((gpio_bits >> i) & 1) && VALID_GPIO(i))
			gpio_config_in(i, pull_mode, 0);
	}
	return;
}


// Funciones para leer y escribir en pines GPIO compatibles:
uint8_t gpio_read(uint8_t gpio_num){
	if(READ_REG_BIT(REG_GPIO_ENABLE, REG_BIT_GPIO_X(gpio_num)) == GPIO_INPUT){
		// Read bit == 0 (input or disabled):
		return READ_INPUT_PIN(gpio_num);
	}
	else{
		// Read bit == 1 (output):
		return READ_OUTPUT_PIN(gpio_num);
	}	
}

void gpio_write(uint8_t gpio_num, uint8_t state){
	// Si el GPIO está configurado como entrada en el registro de habilitación,
	// no escribe nada y retorna:
	if(READ_REG_BIT(REG_GPIO_ENABLE, REG_BIT_GPIO_X(gpio_num)) == GPIO_INPUT)
		return;
	
	// El GPIO está configurado como salida y se escribe el estado deseado:
	if(state == 0)
		CLEAR_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
	else
		SET_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
		
	return;
}

uint8_t gpio_toggle(uint8_t gpio_num){
	// Si el GPIO está configurado como salida en el registro de habilitación,
	// escribe el valor opuesto al estado actual y lo retorna:
	if(READ_REG_BIT(REG_GPIO_ENABLE, REG_BIT_GPIO_X(gpio_num)) == GPIO_OUTPUT){
		TOGGLE_OUTPUT_BITS(REG_BIT_GPIO_X(gpio_num));
		return READ_OUTPUT_PIN(gpio_num) >= 1;
	}
	return 0;
}



