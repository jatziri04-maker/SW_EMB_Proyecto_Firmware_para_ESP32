#ifndef GPIO_2026_H
#define GPIO_2026_H

#include <stdint.h>

// **** Secciones del archivo:
// - Prototipos de funciones para configurar GPIOs como entradas o salidas.




/**************************************************************************/
// **** Prototipos de funciones:

// Funciones para configurar GPIOs como salidas binarias normales:
void gpio_config_out(uint8_t gpio_num);
void gpio_config_out_bits(uint32_t gpio_bits);

// Funciones para configurar GPIOs como entradas binarias normales:
void gpio_config_in(uint8_t gpio_num, uint8_t pull_mode);
void gpio_config_in_bits(uint32_t gpio_bits, uint8_t pull_mode);




#endif /* GPIO_2026_H */
