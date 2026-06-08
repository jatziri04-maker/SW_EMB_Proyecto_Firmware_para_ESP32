/*										CAPA DE APLICACIÓN  
   
					BTN1= activa secuencia			SECUENCIA: R -> G -> B y se repite
					BTN2= detiene secuencia	
					
					DESARROLLADORES:
						->Jatziri Dennise Romero Bustillos (22061040)	
						->Abdiel Alejandro Rodríguez Coronado (22061055)					   
*/


#include "arch/sys_arch.h"
#include "freertos/projdefs.h"

#define VERSION -1

#if VERSION == 0

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

//Manda a llamar a la capa BSP o HAL

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
#include "hw_registers_gpio.h"
#include "gpio_2026.h"




#define LED_BUILTIN	2
#define LED_YELLOW	4
#define LED_RED		5

#define OUTPUTS_INVERTED true

#define BTN_LEFT	18
#define BTN_RIGHT	19

#define INPUTS_INVERTED	true




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

#endif