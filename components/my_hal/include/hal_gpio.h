#ifndef HAL_GPIO_H
#define HAL_GPIO_H

#include <stdint.h>
#include <stdbool.h>
#include "driver_gpio.h"
#include "hal_button.h"
#include "hal_led.h"


// **** Secciones del archivo:
// - Tipos de datos.
// - Variables globales.
// - Prototipos de funciones para configurar GPIOs como LEDs.
// - Prototipos de funciones para manipular y leer LEDs.




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
	bool		_inverted_logic;
} gpio_base_t;

typedef struct{
	gpio_base_t	_gpio;
	bool		_state;
	bool		_past_state;
	bool		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_bool_t;

typedef struct{
	gpio_base_t	_gpio;
	uint8_t		_state;
	uint8_t		_past_state;
	uint8_t		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_uint8_t;

typedef struct{
	gpio_base_t	_gpio;
	uint16_t		_state;
	uint16_t		_past_state;
	uint16_t		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_uint16_t;

typedef struct{
	gpio_base_t	_gpio;
	uint32_t		_state;
	uint32_t		_past_state;
	uint32_t		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_uint32_t;

typedef struct{
	gpio_base_t	_gpio;
	uint64_t		_state;
	uint64_t		_past_state;
	uint64_t		_future_state;
	uint64_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_uint64_t;

typedef struct{
	gpio_base_t	_gpio;
	int8_t		_state;
	int8_t		_past_state;
	int8_t		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_int8_t;

typedef struct{
	gpio_base_t	_gpio;
	int16_t		_state;
	int16_t		_past_state;
	int16_t		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_int16_t;

typedef struct{
	gpio_base_t	_gpio;
	int32_t		_state;
	int32_t		_past_state;
	int32_t		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_int32_t;

typedef struct{
	gpio_base_t	_gpio;
	int64_t		_state;
	int64_t		_past_state;
	int64_t		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_int64_t;

typedef struct{
	gpio_base_t	_gpio;
	float		_state;
	float		_past_state;
	float		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_float_t;

typedef struct{
	gpio_base_t	_gpio;
	double		_state;
	double		_past_state;
	double		_future_state;
	uint32_t	_last_change_time_ms;
	gpio_object_type_e _type;
} gpio_double_t;

typedef void* gpio_ptr;
typedef void* gpio_state;



/**************************************************************************/
// **** Prototipos globales:

// Función para configurar GPIO:
void hal_gpio_init(void *gpio);

// Funciones para manipular y leer estado de GPIO:
void *hal_gpio_get_state(void *gpio);





#endif /* HAL_GPIO_H */
