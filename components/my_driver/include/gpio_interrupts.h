#ifndef GPIO_INTERRUPTS_H
#define GPIO_INTERRUPTS_H

#include <stdint.h>

#include "hw_registers_interrupts.h"
#include "gpio_2026.h"

// **** Secciones del archivo:
// - Tipos de datos.
// - Prototipos de funciones para configurar GPIOs con interrupciones.




/**************************************************************************/
// **** Tipos de datos:

typedef enum{
	DISABLED 		= 0,
	RISING_EDGE		= 1,
	FALLING_EDGE	= 2,
	ANY_EDGE		= 3,
	LOW_LEVEL		= 4,
	HIGH_LEVEL		= 5,
} intr_type_e;

typedef enum{
	CPU_PRO = 0,
	CPU_APP = 1
} cpu_type_e;



/**************************************************************************/
// **** Variables globales:

extern uint8_t led_test_flag;




/**************************************************************************/
// **** Prototipos de funciones:

void IRAM_ATTR gpio_isr_handler_wrapper(void *arg);

// Funciones generales para configurar entrada con interrupciones:
void gpio_config_in_intr(uint8_t gpio_num, gpio_mode_e pull_mode, intr_type_e intr_type, void (*isr_handler_ptr)(void *args));

// Funciones para habilitar y deshabilitar interrupciones en GPIO:
void gpio_disable_intr(uint8_t gpio_num);
void gpio_enable_intr(uint8_t gpio_num, uint8_t int_ena_cfg, intr_type_e intr_type);

// Funciones para configurar la matriz de interrupciones:
void gpio_config_intr_matrix(cpu_type_e cpu_type, uint8_t cpu_interrupt);

// Función para enlazar ISR a la interrupción:
void gpio_register_isr_handler(void (*isr_handler_ptr)(void *args), uint8_t level);

// Función para habilitar interrupción en CPU:
void enable_cpu_interrupt(uint8_t level);


#endif /* GPIO_INTERRUPTS_H */
