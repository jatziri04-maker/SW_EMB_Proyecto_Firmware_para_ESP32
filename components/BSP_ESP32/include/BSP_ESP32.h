/**
 * CAPA BSP (Board Support Package) 
 *\b Description: Capa específica para la ESP32-PANTHER48, se inicializan lo botones en los GPIOS 18 y 19 
 *integrados en la tarjeta, los RGB (en GPIOS 12,13,Y 14) y otros 5 LEDS
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
 */

/*Archivos de cabecera*/
#ifndef BSP_GPIO_H
#define BSP_GPIO_H
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "hal_button.h"
#include "gpio_2026.h"

// MAPEOS (hardware específico de la tarjeta ESP32-PANTHER48 ) debe usar HAL
#define BTN_LEFT	18
#define BTN_RIGHT	19
#define INPUTS_INVERTED	true
#define LED_STATE_4	4
#define LED_R 		14
#define LED_G		12
#define LED_B		13
#define LED_5		5
#define LED_2		2
#define LED_16		16
#define LED_17		17

#define OUTPUTS_INVERTED true


//Prototipos de funciones de BSP
void bsp_init(void); 
bool bsp_btn1_pressed(void);
bool bsp_btn2_pressed(void);

void bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b);
void bsp_led_state_set(void);
void bsp_system_stop(void);

#endif

