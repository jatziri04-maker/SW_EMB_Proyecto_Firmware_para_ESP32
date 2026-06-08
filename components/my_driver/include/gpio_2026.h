#ifndef GPIO_2026_H
#define GPIO_2026_H

#include <stdint.h>

// **** Secciones del archivo:
// - Tipos de datos.
// - Variables globales.
// - Prototipos de funciones para configurar GPIOs como entradas o salidas.




/**************************************************************************/
// **** Tipos de datos:

typedef enum{
	OUTPUT_MODE,
	OUTPUT_PWM_MODE,
	INPUT_MODE,
	INPUT_PULLUP_MODE,
	INPUT_PULLDOWN_MODE,
	INPUT_ANALOG_MODE
} gpio_mode_e;




/**************************************************************************/
// **** Variables globales:

extern uint64_t inverted_gpios;




/**************************************************************************/
// **** Prototipos de funciones:

// Funciones para configurar GPIOs como salidas binarias normales:
void gpio_config_out(uint8_t gpio_num, uint8_t invert_logic);
void gpio_config_out_bits(uint32_t gpio_bits);

// Funciones para configurar GPIOs como entradas binarias normales:
void gpio_config_in(uint8_t gpio_num, gpio_mode_e pull_mode, uint8_t invert_logic);
void gpio_config_in_bits(uint32_t gpio_bits, gpio_mode_e pull_mode);

// Funciones para leer y escribir en pines GPIO compatibles:
uint8_t gpio_read(uint8_t gpio_num);
void	gpio_write(uint8_t gpio_num, uint8_t state);
uint8_t	gpio_toggle(uint8_t gpio_num);
uint8_t has_inverted_logic(uint8_t gpio_num);




#endif /* GPIO_2026_H */
