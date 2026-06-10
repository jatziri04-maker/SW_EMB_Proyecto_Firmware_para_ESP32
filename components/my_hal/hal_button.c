#include <stdint.h>
#include <stdbool.h>

#include "esp_timer.h"

#include "driver_gpio.h"
#include "hal_button.h"




/**************************************************************************/
// **** Variables globales:

uint16_t DEBOUNCE_TIME_MS = 200;




/**************************************************************************/
// **** Definiciones de funciones:

// Función para configurar GPIO como botón:
void button_init(button_t* btn, uint8_t pin, gpio_mode_e pull_mode, uint8_t invert_logic){
	btn->_pin 			= pin;
	btn->_state			= false;
	btn->_past_state	= false;
	
	btn->_last_press_time_ms = 0;
	
	gpio_config_in(pin, pull_mode, invert_logic);
	
	return;
}


// Funciones para manipular y leer estado del botón:
bool button_get_state(button_t* btn){
	btn->_state = gpio_read(btn->_pin);
	return btn->_state;
}


bool button_get_past_state(button_t* btn){
	return btn->_past_state;
}


void button_set_past_state(button_t* btn){
	btn->_past_state = btn->_state;
	return;
}


// Función para identificar si el botón ha sido presionado (transición):
bool button_was_pressed(button_t* btn){
	uint32_t now = esp_timer_get_time() / 1000;
	
	if(now - btn->_last_press_time_ms < DEBOUNCE_TIME_MS) 
		return false;
	
	
	bool is_pressed = false;
	
	if(button_get_state(btn) == true && button_get_past_state(btn) == false){
		is_pressed = true;
		btn->_last_press_time_ms = now;
	}
	
	button_set_past_state(btn);
	return is_pressed;
}