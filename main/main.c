/*										CAPA DE APLICACIÓN  
   
					BTN1= activa secuencia			SECUENCIA: R -> G -> B y se repite
					BTN2= detiene secuencia	
					
					DESARROLLADORES:
						->Jatziri Dennise Romero Bustillos (22061040)	
						->Abdiel Alejandro Rodríguez Coronado (22061055)					   
*/

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//Manda a llamar a la capa BSP ahora tiene que llamar a la capa del HAL 
#include "BSP_ESP32.h"
#include "../BSP_ESP32.c"

void app_main(void)
{
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
