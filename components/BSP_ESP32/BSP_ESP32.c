#include <stdio.h>
#include "my_driver.h"
#include "my_hal.h"
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
	
    gpio_config_in(BTN1, INPUT_PULLUP_MODE, true);
    gpio_config_in(BTN2, INPUT_PULLUP_MODE, true);

    gpio_config_out(LED_R, true);
    gpio_config_out(LED_G, true);
    gpio_config_out(LED_B, true);
}

bool bsp_btn1_pressed(void)
{
    return gpio_read(BTN1);
}

bool bsp_btn2_pressed(void)
{
    return gpio_read(BTN2);
}

void bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    gpio_write(LED_R, r);
    gpio_write(LED_G, g);
    gpio_write(LED_B, b);
}
