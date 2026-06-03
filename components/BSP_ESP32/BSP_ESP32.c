#include <stdio.h>
#include "BSP_ESP32.h"
#include "HAL.h"

void bsp_init(void)
{
    gpio_config_in(&IO_MUX_GPIO18_REG, BTN1, PULL_WPD);
    gpio_config_in(&IO_MUX_GPIO19_REG, BTN2, PULL_WPD);

    gpio_config_out(&IO_MUX_GPIO12_REG, LED_R);
    gpio_config_out(&IO_MUX_GPIO13_REG, LED_G);
    gpio_config_out(&IO_MUX_GPIO14_REG, LED_B);
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
