#include <stdint.h>
#include <stdbool.h>

#include "rom/ets_sys.h"
#include "esp_intr_alloc.h"

#include "hw_registers_general_macros.h"
#include "hw_registers_gpio.h"
#include "hw_registers_interrupts.h"
#include "gpio_2026.h"
#include "gpio_interrupts.h"
#include "soc/interrupts.h"


// **** Secciones del archivo:
// - Definición de funciones para configurar GPIOs con interrupciones.




/**************************************************************************/
// **** Variables globales:

uint8_t led_test_flag = 0;




/**************************************************************************/
// **** Funciones para configurar GPIOs con interrupciones:

// ISR default para manejar las interrupciones:
void IRAM_ATTR gpio_isr_handler_wrapper(void *arg){
	
	/*
	// Reads the interrupt status to know which pin triggered it:
	uint32_t intr_status 	= READ_REG(REG_GPIO_STATUS);
	uint32_t intr_status_1	= READ_REG(REG_GPIO_STATUS1);
	
	// Clears the interrupt for the pin that triggered it:
	bool gpio_intr_found = false;
	uint8_t gpio_num = 0;
	
	for(gpio_num = 0; gpio_num <= 31; gpio_num++){
		if((REG_BIT_GPIO_X(gpio_num) & intr_status) != 0){
			gpio_intr_found = true;
			CLEAR_REG_BITS(REG_GPIO_STATUS, REG_BIT_GPIO_X(gpio_num));
			break;
		}
	}
	
	if(!gpio_intr_found){
		for(gpio_num = 32; gpio_num <= 39; gpio_num++){
			if((REG_BIT_GPIO_X(gpio_num) & intr_status_1) != 0){
				CLEAR_REG_BITS(REG_GPIO_STATUS1, REG_BIT_GPIO_X(gpio_num));
				break;
			}
		}
	}
	
	if(gpio_num == 19){
		TOGGLE_OUTPUT_BITS(REG_BIT_GPIO_X(2));
	}
	*/
	
	//CLEAR_REG_BITS(REG_GPIO_STATUS, REG_BIT_GPIO_X(19));
	//TOGGLE_OUTPUT_BITS(REG_BIT_GPIO_X(2));
	
	uint8_t gpio_num = (uint8_t)(uint32_t)arg;
	
	SET_REG_BITS(REG_GPIO_STATUS_W1TC, REG_BIT_GPIO_X(gpio_num));
	led_test_flag = 1;
	
	return;
}



// Funciones generales para configurar entrada con interrupciones:

void gpio_config_in_intr(uint8_t gpio_num, gpio_mode_e pull_mode, intr_type_e intr_type, void (*isr_handler_ptr)(void *args)){
	
	gpio_config_in(gpio_num, pull_mode, false);
	
	
	//gpio_config_intr_matrix(PERIPHERAL_EDGE_INTR_PRIORITY_4);	
	
	//gpio_register_isr_handler(isr_handler_ptr, 4);
	
	//enable_cpu_interrupt(4);
	
	if(intr_type == DISABLED){
		gpio_disable_intr(gpio_num);
		return;		
	}
	else{
		gpio_enable_intr(gpio_num, INT_ENA_APP_IE, intr_type);
	}
	
	uint32_t intr_flags = ESP_INTR_FLAG_EDGE;
	
	 esp_err_t ret = esp_intr_alloc(
		ETS_GPIO_INTR_SOURCE, 
		intr_flags, 
		isr_handler_ptr, 
		(void*)(uint32_t)gpio_num, 
		NULL
	);
	
	
    if(ret != ESP_OK) {
        // Handle error - interrupt allocation failed
        led_test_flag = 0xFF;  // Error indicator
    }
    else{
		printf("Interrupt configured\n");
	}
	
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


// Funciones para configurar la matriz de interrupciones:
void gpio_config_intr_matrix(uint8_t cpu_interrupt){
	WRITE_REG_FIELD(
		REG_DPORT_APP_GPIO_INTERRUPT_MAP, 
		DPORT_APP_X_MAP_MASK, DPORT_APP_X_MAP_SHIFT, cpu_interrupt
	);
	
	return;
}


// Función para enlazar ISR a la interrupción:
void gpio_register_isr_handler(void (*isr_handler_ptr)(void *args), uint8_t level){
	
	uint32_t isr_address = (uint32_t)isr_handler_ptr;
	
    volatile uint32_t *vector_reg;
    switch(level) {
        case 1: vector_reg = REG_PIDCTRL_INTERRUPT_ADDR_1; break;
        case 2: vector_reg = REG_PIDCTRL_INTERRUPT_ADDR_2; break;
        case 3: vector_reg = REG_PIDCTRL_INTERRUPT_ADDR_3; break;
        case 4: vector_reg = REG_PIDCTRL_INTERRUPT_ADDR_4; break;
        case 5: vector_reg = REG_PIDCTRL_INTERRUPT_ADDR_5; break;
        case 6: vector_reg = REG_PIDCTRL_INTERRUPT_ADDR_6; break;
        case 7: vector_reg = REG_PIDCTRL_INTERRUPT_ADDR_7; break;
        default: return;
    }
	
	WRITE_REG(vector_reg, isr_address);
	
	return;
}


// Función para habilitar interrupción en CPU:
void enable_cpu_interrupt(uint8_t level){
    // level should be 1-7, bit position = level
    uint32_t intr_bit = (1 << level);
    /*
    __asm__ volatile (
        "rsr    %0, intenable\n"  // Read current enables
        "or     %0, %0, %1\n"     // OR with our bit
        "wsr    %0, intenable\n"  // Write back
        : "=&r"(intr_bit) 
        : "r"(intr_bit)
    );
    */
    
	return;
}
