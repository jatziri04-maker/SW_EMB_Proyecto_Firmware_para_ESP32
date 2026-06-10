/**
 * CAPA HAL (Hardware Abstraction Layer)
 * \b Description: Archivo hal_gpio.h donde se definen los tipos de datos, variables globales y prototipos de funciones para configurar y manipular pines GPIO de manera general.
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
*/

#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include "driver_gpio.h"


// **** Secciones del archivo:
// - Tipos de datos.
// - Variables globales.
// - Prototipos de funciones para configurar GPIOs genérico.
// - Prototipos de funciones para manipular y leer GPIO.




/**************************************************************************/
// **** Tipos de datos:

typedef enum{
	GPIO_BOOL = 0,
	GPIO_UINT8,
	GPIO_UINT16,
	GPIO_UINT32,
	GPIO_UINT64,
	
	GPIO_INT8,
	GPIO_INT16,
	GPIO_INT32,
	GPIO_INT64,
	
	GPIO_FLOAT,
	GPIO_DOUBLE
	
} gpio_object_type_e;


typedef struct{
	uint8_t 	_pin;
	gpio_mode_e	_mode;
	bool		_invert_logic;
} gpio_base_t;


typedef struct{
	gpio_base_t 		_gpio;
	
	union{
		bool		bool_val;
		
		uint8_t		u8_val;
		uint16_t	u16_val;
		uint32_t	u32_val;
		uint64_t	u64_val;
		
		int8_t		s8_val;
		int16_t		s16_val;
		int32_t		s32_val;
		int64_t		s64_val;
		
		float		float_val;
		double		double_val;
	} state, past_state, future_state;
	
	uint32_t			_last_change_time_ms;
	gpio_object_type_e 	_type;
} gpio_generic_t;

typedef gpio_generic_t* gpio_ptr;




/**************************************************************************/
// **** Variables globales:

extern uint32_t LAST_CHANGE_MIN_TIME_MS;




/**************************************************************************/
// **** Prototipos globales:

// **** Función para configurar GPIO:
void hal_gpio_init(gpio_ptr gpio, gpio_object_type_e type, uint8_t pin, gpio_mode_e mode, bool invert_logic);

// **** Funciones para manipular y leer estado de GPIO:

// Funciones para leer estado:
bool 		hal_gpio_bool_get_state(gpio_ptr gpio);
uint8_t 	hal_gpio_u8_get_state(gpio_ptr gpio);
uint16_t 	hal_gpio_u16_get_state(gpio_ptr gpio);
uint32_t 	hal_gpio_u32_get_state(gpio_ptr gpio);
uint64_t 	hal_gpio_u64_get_state(gpio_ptr gpio);

int8_t 	hal_gpio_s8_get_state(gpio_ptr gpio);
int16_t	hal_gpio_s16_get_state(gpio_ptr gpio);
int32_t hal_gpio_s32_get_state(gpio_ptr gpio);
int64_t hal_gpio_s64_get_state(gpio_ptr gpio);

float 	hal_gpio_float_get_state(gpio_ptr gpio);
double 	hal_gpio_double_get_state(gpio_ptr gpio);


// Funciones para leer estado pasado:
bool 		hal_gpio_bool_get_past_state(gpio_ptr gpio);
uint8_t 	hal_gpio_u8_get_past_state(gpio_ptr gpio);
uint16_t 	hal_gpio_u16_get_past_state(gpio_ptr gpio);
uint32_t 	hal_gpio_u32_get_past_state(gpio_ptr gpio);
uint64_t 	hal_gpio_u64_get_past_state(gpio_ptr gpio);

int8_t 		hal_gpio_s8_get_past_state(gpio_ptr gpio);
int16_t		hal_gpio_s16_get_past_state(gpio_ptr gpio);
int32_t 	hal_gpio_s32_get_past_state(gpio_ptr gpio);
int64_t 	hal_gpio_s64_get_past_state(gpio_ptr gpio);

float 		hal_gpio_float_get_past_state(gpio_ptr gpio);
double 		hal_gpio_double_get_past_state(gpio_ptr gpio);


// Funciones para manipular estado:
void hal_gpio_bool_set_state(gpio_ptr gpio, bool state);
void hal_gpio_u8_set_state(gpio_ptr gpio, uint8_t state);
void hal_gpio_u16_set_state(gpio_ptr gpio, uint16_t state);
void hal_gpio_u32_set_state(gpio_ptr gpio, uint32_t state);
void hal_gpio_u64_set_state(gpio_ptr gpio, uint64_t state);

void hal_gpio_s8_set_state(gpio_ptr gpio, int8_t state);
void hal_gpio_s16_set_state(gpio_ptr gpio, int16_t state);
void hal_gpio_s32_set_state(gpio_ptr gpio, int32_t state);
void hal_gpio_s64_set_state(gpio_ptr gpio, int64_t state);

void hal_gpio_float_set_state(gpio_ptr gpio, float state);
void hal_gpio_double_set_state(gpio_ptr gpio, double state);


// Funciones para actualizar estado pasado y detectar transiciones:
void hal_gpio_set_past_state(gpio_ptr gpio);

bool hal_gpio_was_changed(gpio_ptr gpio);




#endif /* HAL_GPIO_H */