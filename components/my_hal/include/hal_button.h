/**
 * CAPA HAL (Hardware Abstraction Layer)
 * \b Description: Archivo hal_button.h donde se definen los tipos de datos, variables globales y prototipos de funciones para configurar y manipular botones.
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
*/

#ifndef HAL_BUTTON_H
#define HAL_BUTTON_H


#include <stdint.h>
#include <stdbool.h>

#include "driver_gpio.h"


// **** Secciones del archivo:
// - Tipos de datos.
// - Variables globales.
// - Prototipos de funciones para configurar GPIOs como botones.
// - Prototipos de funciones para manipular y leer estado de botones.
// - Prototipos de funciones para ver si el botón ha sido presionado.



/**************************************************************************/
// **** Tipos de datos:

typedef struct{
	uint8_t 	_pin;
	uint8_t 	_state;
	uint8_t 	_past_state;
	uint32_t	_last_press_time_ms;
} button_t;




/**************************************************************************/
// **** Variables globales:

extern uint16_t DEBOUNCE_TIME_MS;




/**************************************************************************/
// **** Prototipos de funciones:

// Función para configurar GPIO como botón:
void hal_button_init(button_t *btn, uint8_t pin, gpio_mode_e pull_mode, bool invert_logic);

// Funciones para manipular y leer estado del botón:
bool hal_button_get_state(button_t *btn);
bool hal_button_get_past_state(button_t *btn);
void hal_button_set_past_state(button_t *btn);

// Función para identificar si el botón ha sido presionado (transición):
bool hal_button_was_pressed(button_t *btn);


#endif /* HAL_BUTTON_H */
