#include <stdio.h>
#include "Drive_Gpio2026.h"
#include "my_HAL.h"
#include "BSP_ESP32.h"

void bsp_init(void)
{
	/* Ejemplo con nuevo driver:
	
	gpio_config_in(BTN_LEFT, INPUT_NO_PULL_MODE/INPUT_PULLUP_MODE/INPUT_PULLDOWN_MODE);
	gpio_config_out(LED_BUILTIN);
	
	gpio_read(BTN_LEFT);
	gpio_write(LED_BUILTIN, false/true);
	gpio_toggle(LED_BUILTIN);
	
	Nota:
	BTN_LEFT 	== Número de pin (18)
	LED_BUILTIN == Número de pin (2)
	
	*/
	
    bsp_gpio_config_in(BTN_LEFT, INPUT_PULLUP_MODE);
    bsp_gpio_config_in(BTN_RIGHT, INPUT_PULLUP_MODE);

    bsp_gpio_config_out(LED_R);
    bsp_gpio_config_out(LED_G);
    bsp_gpio_config_out(LED_B);
}

bool bsp_btn1_pressed(void)
{
    return bsp_gpio_read(BTN_LEFT);
}

bool bsp_btn2_pressed(void)
{
    return bsp_gpio_read(BTN_RIGHT);
}

void bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    bsp_gpio_write(LED_R, true);
    bsp_gpio_write(LED_G, true);
    bsp_gpio_write(LED_B, true);
}
