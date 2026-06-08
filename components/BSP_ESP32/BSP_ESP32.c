#include <stdio.h>
#include "Drive_Gpio2026.h"
#include "my_HAL.h"
#include "BSP_ESP32.h"
#include "hal_button.h"

void bsp_init(void)
{
	/* Ejemplo con nuevo driver:
	
	gpio_config_in(BTN_LEFT, INPUT_NO_PULL_MODE/INPUT_PULLUP_MODE/INPUT_PULLDOWN_MODE);
	gpio_config_out(LED_BUILTIN);
	
	gpio_read(BTN_LEFT);
	gpio_write(LED_BUILTIN, false/true);
	gpio_toggle(LED_BUILTIN, false/true);
	
	Nota:
	BTN_LEFT 	== Número de pin (18)
	LED_BUILTIN == Número de pin (2)
	
	*/
	
    button_init(&left_button, BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	button_init(&right_button, BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);

	bsp_gpio_config_out(LED_STATE, false);
    bsp_gpio_config_out(LED_R,OUTPUTS_INVERTED);
    bsp_gpio_config_out(LED_G,OUTPUTS_INVERTED);
    bsp_gpio_config_out(LED_B,OUTPUTS_INVERTED);
    
   
}
bool bsp_btn1_pressed(void)
{
	if(button_get_state(&right_button)) {
		return button_was_pressed(&right_button);
	}else return 0;
}

bool bsp_btn2_pressed(void)
{
	if(button_get_state(&left_button)) { 
		return button_get_state(&left_button);
    }else return 0;
}

void bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b)
{
    bsp_gpio_write(LED_R, true);
    bsp_gpio_write(LED_G, true);
    bsp_gpio_write(LED_B, true);
}

void bsp_led_state_set(void){
	gpio_toggle(LED_STATE,false);
	
}

void bsp_system_stop(void){
	 bsp_rgb_set(0,0,0);
    gpio_write(LED_STATE, 0);
}
