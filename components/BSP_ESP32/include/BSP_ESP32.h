/*								CAPA BSP (Board Support Package)
Capa específica para una ESP32 wroom, solo se tienen los botones de boot y RST integrados en la tarjeta 
y se agregaó como Hardware extra un arreglo de LED RGB (Cátodo comun)y un par de botones en los GPIOS 18 y 19
para poder llevar a cabo la aplicación 

*/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include <stdbool.h>
#include <stdint.h>
#include "hal_button.h"

// MAPEOS/MASCARAS (hardware específico de mi ESP32) debe usar HAL
#define BTN_LEFT	18
#define BTN_RIGHT	19
#define INPUTS_INVERTED	false
#define LED_STATE	2
#define LED_R 		13
#define LED_G		12
#define LED_B		14
#define OUTPUTS_INVERTED true

button_t left_button = {0};
button_t right_button = {0};

// API BSP
void bsp_init(void); 
bool bsp_btn1_pressed(void);
bool bsp_btn2_pressed(void);

void bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b);
void bsp_led_state_set(void);

#endif

