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
	
    j_gpio_config_in(&IO_MUX_GPIO18_REG, BTN1, PULL_WPD);
    j_gpio_config_in(&IO_MUX_GPIO19_REG, BTN2, PULL_WPD);

    j_gpio_config_out(&IO_MUX_GPIO12_REG, LED_R);
    j_gpio_config_out(&IO_MUX_GPIO13_REG, LED_G);
    j_gpio_config_out(&IO_MUX_GPIO14_REG, LED_B);
}

bool bsp_btn1_pressed(void)
{
    return j_gpio_read(BTN1);
}

bool bsp_btn2_pressed(void)
{
    return j_gpio_read(BTN2);
}

void bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    j_gpio_write(LED_R, r);
    j_gpio_write(LED_G, g);
    j_gpio_write(LED_B, b);
}
