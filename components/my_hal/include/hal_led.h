#ifndef HAL_LED_H
#define HAL_LED_H


#include <stdint.h>
#include <stdbool.h>


// **** Secciones del archivo:
// - Tipos de datos.
// - Variables globales.
// - Prototipos de funciones para configurar GPIOs como LEDs.
// - Prototipos de funciones para manipular y leer LEDs.




/**************************************************************************/
// **** Tipos de datos:

typedef struct{
	uint8_t _pin;
	uint8_t _state;
} led_t;




/**************************************************************************/
// **** Variables globales:




/**************************************************************************/
// **** Prototipos de funciones:

// **** Función para configurar GPIO como LED:
void hal_led_init(led_t *led, uint8_t pin, bool invert_logic);

// **** Funciones para manipular y leer estado del LED:
uint8_t hal_led_get_state(led_t *led);

void hal_led_turn_on(led_t *led);
void hal_led_turn_off(led_t *led);
void hal_led_toggle(led_t *led);

void hal_led_set_state(led_t *led, uint8_t state);


#endif /* HAL_LED_H */
