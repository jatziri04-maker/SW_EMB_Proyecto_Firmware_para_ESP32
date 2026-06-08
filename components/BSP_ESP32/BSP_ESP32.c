#include <stdio.h>
#include "Drive_Gpio2026.h"
#include "my_HAL.h"
#include "BSP_ESP32.h"
#include "hal_button.h"
#include "gpio_2026.h"

button_t left_button = {0};
button_t right_button = {0};

void bsp_init(void)
{

	gpio_config_out(LED_STATE, OUTPUTS_INVERTED);
    gpio_config_out(LED_R, OUTPUTS_INVERTED);
    gpio_config_out(LED_G, OUTPUTS_INVERTED);
    gpio_config_out(LED_B, OUTPUTS_INVERTED); 
	
    button_init(&left_button, BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	button_init(&right_button, BTN_RIGHT, INPUT_PULLUP_MODE, INPUTS_INVERTED);

	// Inicializar todo apagado
    gpio_write(LED_STATE, false);
    gpio_write(LED_R, false);
    gpio_write(LED_G, false);
    gpio_write(LED_B, false);
    
   printf("Se inicializo BSP... \n\n");
}

bool bsp_btn1_pressed(void)
{
	return button_was_pressed(&left_button);
	
}

bool bsp_btn2_pressed(void)
{
	return button_was_pressed(&right_button);

}

void bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    gpio_write(LED_R, r);
    gpio_write(LED_G, g);
    gpio_write(LED_B, b);
}

void bsp_led_state_set(void){
	gpio_toggle(LED_STATE);
		
}

void bsp_system_stop(void){
	 bsp_rgb_set(0,0,0);
    gpio_write(LED_STATE, 0);
}
