/**
 * CAPA BSP (Board Support Package) 
 *\b Description: archivo BSP.c donde se construyen las funciones para inicializar los GPIOS de la ESP32-PANTHER48
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
 */
#include <stdio.h>
#include "my_bsp.h"


// **** Secciones del archivo:
// - Variables globales.
// - Definición de funciones para configurar y manejar la tarjeta.




/**************************************************************************/
// **** Variables globales:

//Instancias de los botones
button_t left_button = {0};
button_t right_button = {0};




/**************************************************************************/
// **** Definición de funciones:

/**
 *@Function: bsp_init() 
 *@brief Esta funcion inicializa los botones(GPIO 18 y 19) y LEDs (GPIO 2,4,5,16,17,12,13,14)
 *@param[in] void
 *@return void  
*/
void bsp_init(void){
	//Inicializacion de los LEDS 
	driver_gpio_config_out(LED_STATE_4, OUTPUTS_INVERTED);
    driver_gpio_config_out(LED_R, OUTPUTS_INVERTED);
    driver_gpio_config_out(LED_G, OUTPUTS_INVERTED);
    driver_gpio_config_out(LED_B, OUTPUTS_INVERTED); 
    driver_gpio_config_out(LED_5, OUTPUTS_INVERTED); 
    //driver_gpio_config_out(LED_2, OUTPUTS_INVERTED); 
    driver_gpio_config_out(LED_16, OUTPUTS_INVERTED); 
    driver_gpio_config_out(LED_17, OUTPUTS_INVERTED); 
	
	//Inicialización de los botones (GPIO 18 Y 19)
    hal_button_init(&left_button, BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	hal_button_init(&right_button, BTN_RIGHT, INPUT_PULLUP_MODE, INPUTS_INVERTED);

	// Inicializar leds apagados
    driver_gpio_write(LED_STATE_4, false);
    driver_gpio_write(LED_R, false);
    driver_gpio_write(LED_G, false);
    driver_gpio_write(LED_B, false);
    driver_gpio_write(LED_5, false);
    //driver_gpio_write(LED_2, false);
    driver_gpio_write(LED_16, false);
    driver_gpio_write(LED_17, false);
    
   printf("Se inicializo BSP... \n\n");
}


/**
 *@Function: bsp_btn1_pressed()
 *@brief Funcion para leer el cambio de estado del boton1 en GPIO18 y determinar si se ha presionado
 *@param[in] void
 *@return bool: true = si fue presionado, false = si no se presionó 
*/
bool bsp_btn1_pressed(void){
	return hal_button_was_pressed(&left_button);
}

/**
 *@Function: bsp_btn2_pressed()
 *@brief Funcion para leer el cambio de estado del boton1 en GPIO19 y determinar si se ha presionado
 *para usarla hay que declarar un objeto para el botón button_t left_button = {0};
 *@param[in] void
 *@return bool: true = si fue presionado, false = si no se presionó 
*/
bool bsp_btn2_pressed(void){
	return hal_button_was_pressed(&right_button);
}


/**
 *@Function: bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b)
 *@brief Fución para escribir los colores del led rgb 
 *@param[in] entero sin signo de 8 bits, uno por cada color (3), se pone a 1 el color que se vaya a prender y 0 los demás para dejarlos apagados
 *@return void
*/
void bsp_rgb_set(uint8_t r, uint8_t g, uint8_t b){
    driver_gpio_write(LED_R, r);
    driver_gpio_write(LED_G, g);
    driver_gpio_write(LED_B, b);
}


/**
 *@Function: bsp_led_state_set()
 *@brief Función para Led indicador de estado, parpadea o enciende haciendo un toggle
 *@param[in] void
 *@return void
*/
void bsp_led_state_set(void){
		driver_gpio_toggle(LED_STATE_4);
	
		
}


/**
 *@Function: bsp_system_stop()
 *@brief Función de paro del sistema apaga todos los leds 
 *@param[in] void
 *@return void
*/
void bsp_system_stop(void){
	bsp_rgb_set(0,0,0);
    driver_gpio_write(LED_STATE_4, 0);
    driver_gpio_write(LED_16, 0);
    driver_gpio_write(LED_17, 0);
}
