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

led_t led_4 = {0};
led_t led_r = {0};
led_t led_g = {0};
led_t led_b = {0};
led_t led_2 = {0};
led_t led_5 = {0};
led_t led_16 = {0};
led_t led_17 = {0};


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
	hal_led_init(&led_4, LED_4, OUTPUTS_INVERTED);
    hal_led_init(&led_r, LED_R, OUTPUTS_INVERTED);
    hal_led_init(&led_g, LED_G, OUTPUTS_INVERTED);
    hal_led_init(&led_b, LED_B, OUTPUTS_INVERTED); 
    hal_led_init(&led_5, LED_5, OUTPUTS_INVERTED); 
    //hal_led_init(&led_2,LED_2, OUTPUTS_INVERTED); 
    hal_led_init(&led_16, LED_16, OUTPUTS_INVERTED); 
    hal_led_init(&led_17, LED_17, OUTPUTS_INVERTED); 
	
	//Inicialización de los botones (GPIO 18 Y 19)
    hal_button_init(&left_button, BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	hal_button_init(&right_button, BTN_RIGHT, INPUT_PULLUP_MODE, INPUTS_INVERTED);

	// Inicializar leds apagados
    hal_led_turn_off(&led_4);
    hal_led_turn_off(&led_r);
    hal_led_turn_off(&led_g);
    hal_led_turn_off(&led_b);
    //hal_led_turn_off(&led_2);
    hal_led_turn_off(&led_5);
    hal_led_turn_off(&led_16);
    hal_led_turn_off(&led_17);
    
   printf("Se inicializo BSP... \n\n");
}


/**
 *@Function: bsp_btn1_pressed()
 *@brief Funcion para leer el cambio de estado del boton1 en GPIO18 y determinar si se ha presionado
 *para usarla hay que declarar un objeto para el botón button_t left_button = {0};
 *@param[in] void
 *@return bool: true = si fue presionado, false = si no se presionó 
*/
bool bsp_btn1_pressed(void){
	return hal_button_was_pressed(&left_button);
}

/**
 *@Function: bsp_btn2_pressed()
 *@brief Funcion para leer el cambio de estado del boton1 en GPIO19 y determinar si se ha presionado
 *para usarla hay que declarar un objeto para el botón button_t right_button = {0};
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
    hal_led_set_state(&led_r, r);
    hal_led_set_state(&led_g, g);
    hal_led_set_state(&led_b, b);
}


/**
 *@Function: bsp_led_state_set()
 *@brief Función para Led indicador de estado, parpadea o enciende haciendo un toggle
 *@param[in] void
 *@return void
*/
void bsp_led_state_set(void){
		hal_led_toggle(&led_4);
	
		
}


/**
 *@Function: bsp_system_stop()
 *@brief Función de paro del sistema apaga todos los leds
 *@param[in] void
 *@return void
*/
void bsp_system_stop(void){
	bsp_rgb_set(0,0,0);
    hal_led_turn_off(&led_4);
    hal_led_turn_off(&led_5);
    hal_led_turn_off(&led_2);
    hal_led_turn_off(&led_16);
    hal_led_turn_off(&led_17);
}
