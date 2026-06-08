#include <stdint.h>
#include <stdbool.h>

#include "hw_registers_general_macros.h"
#include "hw_registers_gpio.h"
#include "hw_registers_interrupts.h"
#include "gpio_2026.h"
#include "gpio_interrupts.h"


// **** Secciones del archivo:
// - Definición de funciones para configurar GPIOs con interrupciones.




/**************************************************************************/
// **** Funciones para configurar GPIOs con interrupciones:

// ISR default para manejar las interrupciones:

void IRAM_ATTR gpio_isr_handler_wrapper(void *arg){
	
	// Reads the interrupt status to know which pin triggered it:
	uint32_t intr_status 	= READ_REG(REG_GPIO_STATUS);
	uint32_t intr_status_1	= READ_REG(REG_GPIO_STATUS1);
	
	// Clears the interrupt for the pin that triggered it:
	bool gpio_intr_found = false;
	
	for(uint8_t gpio_num = 0; gpio_num <= 31; gpio_num++){
		if((REG_BIT_GPIO_X(gpio_num) & intr_status) != 0){
			gpio_intr_found = true;
			CLEAR_REG_BITS(REG_GPIO_STATUS, REG_BIT_GPIO_X(gpio_num));
		}
	}
	
	if(!gpio_intr_found){
		for(uint8_t gpio_num = 32; gpio_num <= 39; gpio_num++){
			if((REG_BIT_GPIO_X(gpio_num) & intr_status_1) != 0){
				CLEAR_REG_BITS(REG_GPIO_STATUS1, REG_BIT_GPIO_X(gpio_num));
			}
		}
	}
	
	
	
	return;
}

// Funciones generales para configurar entrada con interrupciones:

void gpio_config_in_intr(uint8_t gpio_num, gpio_mode_e pull_mode, intr_type_e intr_type){
	
	gpio_config_in(gpio_num, pull_mode, false);
	
	if(intr_type == DISABLED)
		gpio_disable_intr(gpio_num);
	else
		gpio_enable_intr(gpio_num, INT_ENA_APP_IE, intr_type);
	
	
	
	
	return;
}


void gpio_disable_intr(uint8_t gpio_num){
	
	WRITE_REG_FIELD(
		REG_GPIO_PIN_X(gpio_num),
		GPIO_PIN_X_INT_ENA_MASK, GPIO_PIN_X_INT_ENA_SHIFT, INT_ENA_DISABLED
	);
	WRITE_REG_FIELD(
		REG_GPIO_PIN_X(gpio_num),
		GPIO_PIN_X_INT_TYPE_MASK, GPIO_PIN_X_INT_TYPE_SHIFT, INT_TYPE_DISABLED
	);
	CLEAR_REG_BITS(
		REG_GPIO_PIN_X(gpio_num),
		GPIO_PIN_X_WAKEUP_ENABLE_BIT | GPIO_PIN_X_PAD_DRIVER_BIT
	);
	
	return;
}

void gpio_enable_intr(uint8_t gpio_num, uint8_t int_ena_cfg, intr_type_e intr_type){
	
	WRITE_REG_FIELD(
		REG_GPIO_PIN_X(gpio_num),
		GPIO_PIN_X_INT_ENA_MASK, GPIO_PIN_X_INT_ENA_SHIFT, int_ena_cfg
	);
	WRITE_REG_FIELD(
		REG_GPIO_PIN_X(gpio_num),
		GPIO_PIN_X_INT_TYPE_MASK, GPIO_PIN_X_INT_TYPE_SHIFT, intr_type
	);
	CLEAR_REG_BITS(
		REG_GPIO_PIN_X(gpio_num),
		GPIO_PIN_X_WAKEUP_ENABLE_BIT | GPIO_PIN_X_PAD_DRIVER_BIT
	);
	
	return;
}

