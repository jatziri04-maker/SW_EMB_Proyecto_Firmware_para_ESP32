/*										CAPA DE APLICACIÓN  
   
					BTN1= activa secuencia			SECUENCIA: R -> G -> B y se repite
					BTN2= detiene secuencia	
					
					DESARROLLADORES:
						->Jatziri Dennise Romero Bustillos (22061040)	
						->Abdiel Alejandro Rodríguez Coronado (22061055)					   
*/


#include "gpio_2026.h"
#define VERSION -2
// VERSION >= 0	-> Pruebas de Jatziri
//	- 0: 	Prueba de BSP.
//
// VERSION < 0	-> Pruebas de Alex
//	- -1: 	Prueba simple de driver para GPIO.
//	- -2: 	Prueba simple de HAL para GPIO.



#if VERSION == 0

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//Manda a llamar a la capa BSP ahora tiene que llamar a la capa del HAL 
#include "BSP_ESP32.h"


void app_main(void){
	
    bsp_init();

    bool running = false;
    uint8_t color = 0;

    while(true)
    {
        if(bsp_btn1_pressed()){
            running = true;
            vTaskDelay(pdMS_TO_TICKS(50));
        }

        if(bsp_btn2_pressed()){
            running = false;
            bsp_rgb_set(0,0,0);
            vTaskDelay(pdMS_TO_TICKS(50));
        }

        if(running){
            switch(color){
                case 0: bsp_rgb_set(1,0,0); break;
                case 1: bsp_rgb_set(0,1,0); break;
                case 2: bsp_rgb_set(0,0,1); break;
            }

            color = (color + 1) % 3;

            vTaskDelay(pdMS_TO_TICKS(1000));
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }    
}








#elif VERSION == -1

#include <stdio.h>
#include <stdbool.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "my_driver.h"




#define LED_BUILTIN	2
#define LED_YELLOW	4
#define LED_RED		5

#define OUTPUTS_INVERTED false

#define BTN_LEFT	18
#define BTN_RIGHT	19

#define INPUTS_INVERTED	false




void app_main(){
	//vTaskDelay(pdMS_TO_TICKS(5000));
	//printf("Starting system...\n\n");
	
	gpio_config_out(LED_BUILTIN, OUTPUTS_INVERTED);
	gpio_config_out(LED_YELLOW, OUTPUTS_INVERTED);
	gpio_config_out(LED_RED, OUTPUTS_INVERTED);
	
	gpio_config_in(BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	gpio_config_in(BTN_RIGHT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	
	while(true){
		if(gpio_read(BTN_LEFT) == 0){
			gpio_write(LED_BUILTIN, true);
			gpio_write(LED_YELLOW, true);
			gpio_write(LED_RED, true);
		}
		else{
			gpio_write(LED_BUILTIN, false);
			gpio_write(LED_YELLOW, false);
			gpio_write(LED_RED, false);
		}
		
		
		vTaskDelay(pdMS_TO_TICKS(200));
	}
	
	return;
}	








#elif VERSION == -2

#include <stdio.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"

#include "my_driver.h"
#include "hw_registers_interrupts.h"
#include "gpio_interrupts.h"
#include "my_HAL.h"
#include "hal_button.h"




#define LED_BUILTIN	2
#define LED_YELLOW	4
#define LED_RED		5

#define OUTPUTS_INVERTED false

#define BTN_LEFT	18
#define BTN_RIGHT	19

#define INPUTS_INVERTED	true



void app_main(){
	
	vTaskDelay(pdMS_TO_TICKS(3000));
	printf("Starting system...\n");
	
	gpio_config_out(LED_BUILTIN, OUTPUTS_INVERTED);
	
	button_t left_button = {0};
	button_init(&left_button, BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	
	gpio_config_in_intr(BTN_RIGHT, INPUT_PULLUP_MODE, FALLING_EDGE, gpio_isr_handler_wrapper);
	
	while(true){
		if(button_was_pressed(&left_button)){
			gpio_toggle(LED_BUILTIN);
		}
		
		if(led_test_flag == 1){
			led_test_flag = 0;
			gpio_toggle(LED_BUILTIN);
			printf("Button pressed\n");
		}
			
		//printf("led_test_flag: %d\n", led_test_flag);
		
		/*
		if(gpio_read(BTN_RIGHT) == 0)
			gpio_write(LED_BUILTIN, true);
		else
 			gpio_write(LED_BUILTIN, false);
		*/
		
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	
	return;
}	

#endif /* VERSION */