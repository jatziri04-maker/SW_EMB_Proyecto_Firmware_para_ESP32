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




/**************************************************************************/
// **** Prototipos de funciones:

void IRAM_ATTR gpio_isr_default_handler(void *arg);

// Funciones generales para configurar entrada con interrupciones:
void gpio_config_in_intr(uint8_t gpio_num, gpio_mode_e pull_mode, intr_type_e intr_type);

// Funciones para habilitar y deshabilitar interrupciones en GPIO:
void gpio_disable_intr(uint8_t gpio_num);
void gpio_enable_intr(uint8_t gpio_num, uint8_t int_ena_cfg, intr_type_e intr_type);



#endif /* GPIO_INTERRUPTS_H */
