/**
 * CAPA HAL (Hardware Abstraction Layer)
 * \b Description: Archivo hal_button.c donde se definen las funciones para configurar y manipular botones.
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
*/

#include <stdint.h>
#include <stdbool.h>

#include "esp_timer.h"

#include "driver_gpio.h"
#include "hal_button.h"


// **** Secciones del archivo:
// - Variables globales.
// - Funciones para configurar GPIOs como botones.
// - Funciones para manipular y leer estado de botones.
// - Funciones para ver si el botón ha sido presionado.




/**************************************************************************/
// **** Variables globales:

uint16_t DEBOUNCE_TIME_MS = 200;




/**************************************************************************/
// **** Definiciones de funciones:

// Función para configurar GPIO como botón:
void hal_button_init(button_t* btn, uint8_t pin, gpio_mode_e pull_mode, bool invert_logic){
	btn->_pin 			= pin;
	btn->_state			= false;
	btn->_past_state	= false;
	
	btn->_last_press_time_ms = 0;
	
	driver_gpio_config_in(pin, pull_mode, invert_logic);
	
	return;
}


// Funciones para manipular y leer estado del botón:
bool hal_button_get_state(button_t* btn){
	btn->_state = driver_gpio_read(btn->_pin);
	return btn->_state;
}


bool hal_button_get_past_state(button_t* btn){
	return btn->_past_state;
}


void hal_button_set_past_state(button_t* btn){
	btn->_past_state = btn->_state;
	return;
}


// Función para identificar si el botón ha sido presionado (transición):
bool hal_button_was_pressed(button_t* btn){
	uint32_t now = esp_timer_get_time() / 1000;
	
	if(now - btn->_last_press_time_ms < DEBOUNCE_TIME_MS) 
		return false;
	
	
	bool is_pressed = false;
	
	if(hal_button_get_state(btn) == true && hal_button_get_past_state(btn) == false){
		is_pressed = true;
		btn->_last_press_time_ms = now;
	}
	
	hal_button_set_past_state(btn);
	return is_pressed;
}