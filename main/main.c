/*										CAPA DE APLICACIÓN  
   
					BTN1= activa secuencia			SECUENCIA: R -> G -> B y se repite
					BTN2= detiene secuencia	
					
					DESARROLLADORES:
						->Jatziri Dennise Romero Bustillos (22061040)	
						->Abdiel Alejandro Rodríguez Coronado (22061055)					   
*/



#define VERSION 0
// VERSION >= 0	-> Pruebas de Jatziri
//	-> 0: 	Prueba de BSP.
//
// VERSION < 0	-> Pruebas de Alex
//	-> -1: 	Prueba simple de driver para GPIO.
//	-> -2: 	Prueba simple de HAL para GPIO.



#if VERSION == 1

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//Manda a llamar a la capa BSP 
#include "BSP_ESP32.h"

void app_main(void){
	
    bsp_init();
    bool system_run = false;
    uint8_t cont_color = 0;
    printf("wait button... \n\n");

    while(true)
    {
        if(bsp_btn1_pressed()){
			printf("boton 1 pressed\n");
			printf("Starting system...\n\n");
			system_run = true;
			cont_color = 1;
			bsp_led_state_set();
		}
		
		else if(bsp_btn2_pressed()){
			printf("boton 2 pressed\n");
			printf("System stop...\n\n");
           bsp_system_stop();
           cont_color = 0; 
           system_run = false;
            vTaskDelay(pdMS_TO_TICKS(50));
        }
        
		if(system_run){
			
       		switch(cont_color){
	            case 1: bsp_rgb_set(1,0,0); break;
	            case 2: bsp_rgb_set(0,1,0); break;
	            case 3: bsp_rgb_set(0,0,1); break;
	            
            }
            
            vTaskDelay(pdMS_TO_TICKS(1000));  
            if(cont_color >3) cont_color =0;
        }
		cont_color ++;
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }    
}



#elif VERSION == 1
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "BSP_ESP32.h"

void app_main(void)
{
    printf("Punto 1: Inicio\n");
    vTaskDelay(pdMS_TO_TICKS(100));
    
    printf("Punto 2: Llamando bsp_init\n");
    bsp_init();
    printf("Punto 3: bsp_init completado\n");
    
    printf("Punto 4: Iniciando loop\n");
    
    int counter = 0;
    
    while(true) {
        counter++;
        
        if(counter % 100 == 0) {
            printf("Sistema vivo - contador: %d\n", counter);
        }
        
        if(bsp_btn1_pressed()) {
            printf("Botón 1 presionado!\n");
            bsp_rgb_set(1, 0, 0);
        }
        
        if(bsp_btn2_pressed()) {
            printf("Botón 2 presionado!\n");
            bsp_rgb_set(0, 0, 0);
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
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "my_driver.h"
#include "my_HAL.h"
#include "hal_button.h"




#define LED_BUILTIN	2
#define LED_YELLOW	4
#define LED_RED		5

#define OUTPUTS_INVERTED false

#define BTN_LEFT	18
#define BTN_RIGHT	19

#define INPUTS_INVERTED	false




void app_main(){
	
	gpio_config_out(LED_BUILTIN, OUTPUTS_INVERTED);
	
	button_t left_button = {0};
	button_init(&left_button, BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	
	
	while(true){
		if(button_was_pressed(&left_button)){
			gpio_toggle(LED_BUILTIN);
		}
		
		
		vTaskDelay(pdMS_TO_TICKS(10));
	}
	
	return;
}	

#endif /* VERSION */