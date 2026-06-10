/**
 * CAPA HAL (Hardware Abstraction Layer)
 * \b Description: Archivo hal_gpio.c donde se definen las funciones para configurar y manipular pines GPIO de manera general.
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
*/

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "esp_timer.h"

#include "hal_gpio.h"


// **** Secciones del archivo:
// - Variables globales.
// - Definiciones de funciones para configurar GPIOs genérico.
// - Definiciones de funciones para manipular y leer GPIO.




/**************************************************************************/
// **** Variables globales:

uint32_t LAST_CHANGE_MIN_TIME_MS = 200;




/**************************************************************************/
// **** Definiciones de funciones globales:

// **** Función para configurar GPIO:
void hal_gpio_init(gpio_ptr gpio, gpio_object_type_e type, uint8_t pin, gpio_mode_e mode, bool invert_logic){
	
	if(gpio == NULL) return;
	
	gpio->_gpio._pin 			= pin;
	gpio->_gpio._mode 			= mode;
	gpio->_gpio._invert_logic 	= invert_logic;
	gpio->_type 				= type;
	gpio->_last_change_time_ms 	= 0;
	
	switch(type){
		case GPIO_BOOL:
			gpio->state.bool_val = 0;
			gpio->past_state.bool_val = 0;
			gpio->future_state.bool_val = 0;
			break;
		case GPIO_UINT8:
			gpio->state.u8_val = 0;
			gpio->past_state.u8_val = 0;
			gpio->future_state.u8_val = 0;
			break;
		case GPIO_UINT16:
			gpio->state.u16_val = 0;
			gpio->past_state.u16_val = 0;
			gpio->future_state.u16_val = 0;
			break;
		case GPIO_UINT32:
			gpio->state.u32_val = 0;
			gpio->past_state.u32_val = 0;
			gpio->future_state.u32_val = 0;
			break;
		case GPIO_UINT64:
			gpio->state.u64_val = 0;
			gpio->past_state.u64_val = 0;
			gpio->future_state.u64_val = 0;
			break;
		case GPIO_INT8:
			gpio->state.s8_val = 0;
			gpio->past_state.s8_val = 0;
			gpio->future_state.s8_val = 0;
			break;
		case GPIO_INT16:
			gpio->state.s16_val = 0;
			gpio->past_state.s16_val = 0;
			gpio->future_state.s16_val = 0;
			break;
		case GPIO_INT32:
			gpio->state.s32_val = 0;
			gpio->past_state.s32_val = 0;
			gpio->future_state.s32_val = 0;
			break;
		case GPIO_INT64:
			gpio->state.s64_val = 0;
			gpio->past_state.s64_val = 0;
			gpio->future_state.s64_val = 0;
			break;
		case GPIO_FLOAT:
			gpio->state.float_val = 0;
			gpio->past_state.float_val = 0;
			gpio->future_state.float_val = 0;
			break;
		case GPIO_DOUBLE:
			gpio->state.double_val = 0;
			gpio->past_state.double_val = 0;
			gpio->future_state.double_val = 0;
			break;
		default:
			return;
	}
	
	return;
}

// **** Funciones para leer estado:
bool hal_gpio_bool_get_state(gpio_ptr gpio){
	if(gpio == NULL) return false;
	if(gpio->_type != GPIO_BOOL) return false;
	return gpio->state.bool_val;
}

uint8_t hal_gpio_u8_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_UINT8) return 0;
	return gpio->state.u8_val;
}

uint16_t hal_gpio_u16_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_UINT16) return 0;
	return gpio->state.u16_val;
}

uint32_t hal_gpio_u32_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_UINT32) return 0;
	return gpio->state.u32_val;
}

uint64_t hal_gpio_u64_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_UINT64) return 0;
	return gpio->state.u64_val;
}

int8_t hal_gpio_s8_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_INT8) return 0;
	return gpio->state.s8_val;
}

int16_t hal_gpio_s16_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_INT16) return 0;
	return gpio->state.s16_val;
}

int32_t hal_gpio_s32_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_INT32) return 0;
	return gpio->state.s32_val;
}

int64_t hal_gpio_s64_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_INT64) return 0;
	return gpio->state.s64_val;
}

float hal_gpio_float_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0.0f;
	if(gpio->_type != GPIO_FLOAT) return 0.0f;
	return gpio->state.float_val;
}

double hal_gpio_double_get_state(gpio_ptr gpio){
	if(gpio == NULL) return 0.0;
	if(gpio->_type != GPIO_DOUBLE) return 0.0;
	return gpio->state.double_val;
}

// **** Funciones para leer estado pasado:
bool hal_gpio_bool_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return false;
	if(gpio->_type != GPIO_BOOL) return false;
	return gpio->past_state.bool_val;
}

uint8_t hal_gpio_u8_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_UINT8) return 0;
	return gpio->past_state.u8_val;
}

uint16_t hal_gpio_u16_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_UINT16) return 0;
	return gpio->past_state.u16_val;
}

uint32_t hal_gpio_u32_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_UINT32) return 0;
	return gpio->past_state.u32_val;
}

uint64_t hal_gpio_u64_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_UINT64) return 0;
	return gpio->past_state.u64_val;
}

int8_t hal_gpio_s8_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_INT8) return 0;
	return gpio->past_state.s8_val;
}

int16_t hal_gpio_s16_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_INT16) return 0;
	return gpio->past_state.s16_val;
}

int32_t hal_gpio_s32_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_INT32) return 0;
	return gpio->past_state.s32_val;
}

int64_t hal_gpio_s64_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0;
	if(gpio->_type != GPIO_INT64) return 0;
	return gpio->past_state.s64_val;
}

float hal_gpio_float_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0.0f;
	if(gpio->_type != GPIO_FLOAT) return 0.0f;
	return gpio->past_state.float_val;
}

double hal_gpio_double_get_past_state(gpio_ptr gpio){
	if(gpio == NULL) return 0.0;
	if(gpio->_type != GPIO_DOUBLE) return 0.0;
	return gpio->past_state.double_val;
}

// **** Funciones para manipular estado:
void hal_gpio_bool_set_state(gpio_ptr gpio, bool state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_BOOL) return;
	gpio->state.bool_val = state;
}

void hal_gpio_u8_set_state(gpio_ptr gpio, uint8_t state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_UINT8) return;
	gpio->state.u8_val = state;
}

void hal_gpio_u16_set_state(gpio_ptr gpio, uint16_t state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_UINT16) return;
	gpio->state.u16_val = state;
}

void hal_gpio_u32_set_state(gpio_ptr gpio, uint32_t state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_UINT32) return;
	gpio->state.u32_val = state;
}

void hal_gpio_u64_set_state(gpio_ptr gpio, uint64_t state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_UINT64) return;
	gpio->state.u64_val = state;
}

void hal_gpio_s8_set_state(gpio_ptr gpio, int8_t state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_INT8) return;
	gpio->state.s8_val = state;
}

void hal_gpio_s16_set_state(gpio_ptr gpio, int16_t state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_INT16) return;
	gpio->state.s16_val = state;
}

void hal_gpio_s32_set_state(gpio_ptr gpio, int32_t state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_INT32) return;
	gpio->state.s32_val = state;
}

void hal_gpio_s64_set_state(gpio_ptr gpio, int64_t state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_INT64) return;
	gpio->state.s64_val = state;
}

void hal_gpio_float_set_state(gpio_ptr gpio, float state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_FLOAT) return;
	gpio->state.float_val = state;
}

void hal_gpio_double_set_state(gpio_ptr gpio, double state){
	if(gpio == NULL) return;
	if(gpio->_type != GPIO_DOUBLE) return;
	gpio->state.double_val = state;
}

// **** Funciones para actualizar estado pasado y detectar transiciones:
void hal_gpio_set_past_state(gpio_ptr gpio){
	if(gpio == NULL) return;
	
	switch(gpio->_type){
		case GPIO_BOOL:
			gpio->past_state.bool_val = gpio->state.bool_val;
			break;
		case GPIO_UINT8:
			gpio->past_state.u8_val = gpio->state.u8_val;
			break;
		case GPIO_UINT16:
			gpio->past_state.u16_val = gpio->state.u16_val;
			break;
		case GPIO_UINT32:
			gpio->past_state.u32_val = gpio->state.u32_val;
			break;
		case GPIO_UINT64:
			gpio->past_state.u64_val = gpio->state.u64_val;
			break;
		case GPIO_INT8:
			gpio->past_state.s8_val = gpio->state.s8_val;
			break;
		case GPIO_INT16:
			gpio->past_state.s16_val = gpio->state.s16_val;
			break;
		case GPIO_INT32:
			gpio->past_state.s32_val = gpio->state.s32_val;
			break;
		case GPIO_INT64:
			gpio->past_state.s64_val = gpio->state.s64_val;
			break;
		case GPIO_FLOAT:
			gpio->past_state.float_val = gpio->state.float_val;
			break;
		case GPIO_DOUBLE:
			gpio->past_state.double_val = gpio->state.double_val;
			break;
		default:
			return;
	}
	
	return;
}

bool hal_gpio_was_changed(gpio_ptr gpio){
	if(gpio == NULL) return false;
	
	uint32_t now = esp_timer_get_time() / 1000;
	
	if(now - gpio->_last_change_time_ms < LAST_CHANGE_MIN_TIME_MS) 
		return false;
		
	bool has_changed = false;
	
	switch(gpio->_type){
		case GPIO_BOOL:
			has_changed = (gpio->state.bool_val != gpio->past_state.bool_val);
			break;
		case GPIO_UINT8:
			has_changed = (gpio->state.u8_val != gpio->past_state.u8_val);
			break;
		case GPIO_UINT16:
			has_changed = (gpio->state.u16_val != gpio->past_state.u16_val);
			break;
		case GPIO_UINT32:
			has_changed = (gpio->state.u32_val != gpio->past_state.u32_val);
			break;
		case GPIO_UINT64:
			has_changed = (gpio->state.u64_val != gpio->past_state.u64_val);
			break;
		case GPIO_INT8:
			has_changed = (gpio->state.s8_val != gpio->past_state.s8_val);
			break;
		case GPIO_INT16:
			has_changed = (gpio->state.s16_val != gpio->past_state.s16_val);
			break;
		case GPIO_INT32:
			has_changed = (gpio->state.s32_val != gpio->past_state.s32_val);
			break;
		case GPIO_INT64:
			has_changed = (gpio->state.s64_val != gpio->past_state.s64_val);
			break;
		case GPIO_FLOAT:
			has_changed = (gpio->state.float_val != gpio->past_state.float_val);
			break;
		case GPIO_DOUBLE:
			has_changed = (gpio->state.double_val != gpio->past_state.double_val);
			break;
		default:
			return false;
	}
	
	if(has_changed)
		gpio->_last_change_time_ms = now;
		
	hal_gpio_set_past_state(gpio);
	return has_changed;
}