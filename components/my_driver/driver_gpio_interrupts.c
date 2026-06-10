/**
 * CAPA DRIVER
 * \b Description: Archivo driver_gpio_interrupts.h donde se definen las funciones para configurar y manipular interrupciones de pines GPIO.
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
*/

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
/*
#include "rom/ets_sys.h"
#include "esp_intr_alloc.h"
#include "soc/interrupts.h"
*/
#include "driver/gpio.h"

#include "driver_hw_registers_general.h"
#include "driver_hw_registers_interrupts.h"
#include "driver_gpio.h"
#include "driver_gpio_interrupts.h"


// **** Secciones del archivo:
// - Variables globales.
// - Definición de funciones para configurar GPIOs con interrupciones.




/**************************************************************************/
// **** Variables globales:

uint8_t led_test_flag = 0;




/**************************************************************************/
// **** Funciones para configurar GPIOs con interrupciones:

/**
 *@function: 	driver_gpio_isr_handler_wrapper()
 *@brief 		ISR default para manejar las interrupciones de GPIO.
 *@param[in] 	void *arg Puntero a argumento de tipo genérico.
 *@return 		void
*/
void IRAM_ATTR driver_gpio_isr_handler_wrapper(void *arg){
	
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



// Función general para configurar GPIO como entrada con interrupción:

/**
 *@function: 	driver_gpio_config_in_intr()
 *@brief 		ISR default para manejar las interrupciones de GPIO.
 *@param[in] 	uint8_t gpio_num, gpio_mode_e pull_mode, intr_type_e intr_type, void (*isr_handler_ptr)(void *args)
 *@return 		void
*/
void driver_gpio_config_in_intr(uint8_t gpio_num, gpio_mode_e pull_mode, intr_type_e intr_type, void (*isr_handler_ptr)(void *args)){
	
	driver_gpio_config_in(gpio_num, pull_mode, false);
	/*
    WRITE_REG_FIELD(
        REG_GPIO_PIN_X(gpio_num),
        GPIO_PIN_X_INT_TYPE_MASK, GPIO_PIN_X_INT_TYPE_SHIFT, intr_type
    );
    
	
	//printf("Error after this 1.\n");
	
	driver_gpio_config_intr_matrix(CPU_APP, PERIPHERAL_EDGE_INTR_PRIORITY_1);
	//driver_gpio_config_intr_matrix(CPU_APP, 4);
	//printf("Error after this 2.\n");
	
	driver_gpio_register_isr_handler(isr_handler_ptr, 1);
	//printf("Error after this 3.\n");
	
	driver_enable_cpu_interrupt(1);
	//printf("Error after this 4.\n");
	
	*/
	
	if(intr_type == DISABLED){
		driver_gpio_disable_intr(gpio_num);
		return;		
	}
	else{
		driver_gpio_enable_intr(gpio_num, INT_ENA_APP_IE, intr_type);
	}
	//printf("Error after this 5.\n");
	
	
	
	
	
	/*
	uint32_t intr_flags = ESP_INTR_FLAG_EDGE | ESP_INTR_FLAG_IRAM;
	
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
	*/
	
	
	// Configure button as input with interrupt
	
    // Install ISR service (required for GPIO interrupts)
    gpio_install_isr_service(0);
    
    // Add ISR handler for the button
    gpio_isr_handler_add(gpio_num, isr_handler_ptr, (void*)(uint32_t)gpio_num);  
    
    
    
    printf("Interrupcion configurada en GPIO %d\n", gpio_num);
    
	return;
}


void driver_gpio_disable_intr(uint8_t gpio_num){
	
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
	
	if(gpio_num < 32)
		SET_REG_BITS(REG_GPIO_STATUS_W1TC, REG_BIT_GPIO_X(gpio_num));
	else
 		SET_REG_BITS(REG_GPIO_STATUS1_W1TC, REG_BIT_GPIO_X(gpio_num - 32));
 	
 	/*
	printf(
		"REG_GPIO_PIN_%d (%p) state: 0x%x\n\n", 
		gpio_num,
		REG_GPIO_PIN_X(gpio_num),
		(unsigned int)READ_REG(REG_GPIO_PIN_X(gpio_num))
	);
	*/
	
	return;
}

void driver_gpio_enable_intr(uint8_t gpio_num, uint8_t int_ena_cfg, intr_type_e intr_type){
	
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
	
	if(gpio_num < 32)
		SET_REG_BITS(REG_GPIO_STATUS_W1TC, REG_BIT_GPIO_X(gpio_num));
	else
 		SET_REG_BITS(REG_GPIO_STATUS1_W1TC, REG_BIT_GPIO_X(gpio_num - 32));
 		
	printf(
		"REG_GPIO_PIN_%d (%p) state: 0x%x\n\n", 
		gpio_num,
		REG_GPIO_PIN_X(gpio_num),
		(unsigned int)READ_REG(REG_GPIO_PIN_X(gpio_num))
	);
	
	return;
}


// Funciones para configurar la matriz de interrupciones:
void driver_gpio_config_intr_matrix(cpu_type_e cpu_type, uint8_t cpu_interrupt){
	if(cpu_type == CPU_PRO){
		WRITE_REG_FIELD(
			REG_DPORT_PRO_GPIO_INTERRUPT_MAP,
			DPORT_CPU_X_MAP_MASK, DPORT_CPU_X_MAP_SHIFT, cpu_interrupt
		);
		
		CLEAR_REG_BITS(REG_DPORT_PRO_INTR_STATUS_0, (1UL << 22));
	}
	else if(cpu_type == CPU_APP){
		WRITE_REG_FIELD(
			REG_DPORT_APP_GPIO_INTERRUPT_MAP, 
			DPORT_CPU_X_MAP_MASK, DPORT_CPU_X_MAP_SHIFT, cpu_interrupt
		);
		
		CLEAR_REG_BITS(REG_DPORT_APP_INTR_STATUS_0, (1UL << 22));
	}
	
	return;
}


// Función para enlazar ISR a la interrupción:
void driver_gpio_register_isr_handler(void (*isr_handler_ptr)(void *args), uint8_t level){
	
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
	
	WRITE_REG(vector_reg, (uint32_t)isr_handler_ptr);
	
	return;
}


// Función para habilitar interrupción en CPU:
void enable_cpu_interrupt(uint8_t level){
    // level should be 1-7, bit position = levelvoid enable_cpu_interrupt(uint8_t level){
    uint32_t intr_bit = (1 << level);
    __asm__ volatile (
        "rsr    %0, intenable\n"
        "or     %0, %0, %1\n"
        "wsr    %0, intenable\n"
        : "=&r"(intr_bit) 
        : "r"(intr_bit)
    );
}
