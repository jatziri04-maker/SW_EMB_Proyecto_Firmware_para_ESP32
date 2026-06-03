#include <stdint.h>
#include "hw_registers_gpio.h"
#include "gpio_2026.h"




// Funciones para configurar GPIOs como salidas binarias normales:

void gpio_config_out(uint8_t gpio_num){
	if(VALID_GPIO_OUTPUT(gpio_num)){
		SET_OUTPUT_ENABLE(REG_BIT_GPIO_X(gpio_num));
		CLEAR_OUTPUT(REG_BIT_GPIO_X(gpio_num));
	}
	return;
}

void gpio_config_out_bits(uint32_t gpio_bits){
	uint8_t i;
	
	for(i = 0; i < 40; i++){
		if(((gpio_bits >> i) & 1) && !VALID_GPIO_OUTPUT(i))
			return;
	}
	
	SET_OUTPUT_ENABLE(gpio_bits);
	CLEAR_OUTPUT(gpio_bits);
	
	return;
}


// Funciones para configurar GPIOs como entradas binarias normales:

void gpio_config_in(uint8_t gpio_num, uint8_t pull_mode){
	if(!VALID_GPIO(gpio_num)) return;

	SET_INPUT_ENABLE(REG_BIT_GPIO_X(gpio_num));

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
	
	return;
}

void gpio_config_in_bits(uint32_t gpio_bits, uint8_t pull_mode){
	uint8_t i;
	
	for(i = 0; i < 40; i++){
		if(((gpio_bits >> i) & 1) && VALID_GPIO(i))
			gpio_config_in(i, pull_mode);
	}
	return;
}


// Funciones para leer y escribir en pines GPIO compatibles:
uint8_t gpio_read(uint8_t gpio_num){
	if(READ_REG_BIT(REG_GPIO_ENABLE, REG_BIT_GPIO_X(gpio_num))){
		// Read bit == 1 (input):
		return READ_INPUT(gpio_num);
	}
	else{
		// Read bit == 0 (output or disabled):
		return READ_OUTPUT(gpio_num);
	}	
}

void gpio_write(uint8_t gpio_num, uint8_t state){
	
}



