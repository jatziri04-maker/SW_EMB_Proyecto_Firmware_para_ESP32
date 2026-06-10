/**
 * CAPA HAL (Hardware Abstraction Layer)
 * \b Description: Archivo hal_led.c donde se definen las funciones para configurar y manipular LEDs.
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
*/

#include <stdint.h>
#include <stdbool.h>

#include "driver_gpio.h"
#include "hal_led.h"


// **** Secciones del archivo:
// - Tipos de datos.
// - Variables globales.
// - Definición de funciones para configurar GPIOs como LEDs.
// - Definición de funciones para manipular y leer LEDs.




/**************************************************************************/
// **** Variables globales:




/**************************************************************************/
// **** Definición de funciones:

// **** Función para configurar GPIO como LED:
void hal_led_init(led_t *led, uint8_t pin, bool invert_logic){
	led->_pin 	= pin;
	led->_state	= false;
	
	driver_gpio_config_out(led->_pin, invert_logic);
	
	return;
}

// **** Funciones para manipular y leer estado del LED:

// Función para leer estado del LED:
uint8_t hal_led_get_state(led_t *led){
	led->_state = driver_gpio_read(led->_pin);
	return led->_state;
}


// Función para encender LED:
void hal_led_turn_on(led_t *led){
	led->_state = true;
	
	driver_gpio_write(led->_pin, true);
	
	return;
}


// Función para apagar LED:
void hal_led_turn_off(led_t *led){
	led->_state = false;
	
	driver_gpio_write(led->_pin, false);
	
	return;
}


// Función para togglear LED:
void hal_led_toggle(led_t *led){
	led->_state = driver_gpio_toggle(led->_pin);
	return;
}


// Función para manipular estado del LED:
void hal_led_set_state(led_t *led, uint8_t state){
	led->_state = state;
	
	driver_gpio_write(led->_pin, state);
	
	return;
}
