/**
 * CAPA DE APLICACIÓN  
 *\b Description: BTN1= activa secuencia y BTN2= detiene secuencia		
 * SECUENCIA: R -> G -> B y se repite
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
 */

#define VERSION 0
/*
 *VERSION 0 a 3 pruebas de Jatziri				VERSION 	CARACTERÍSTICAS
 *													0		Secuencia simple (sin RTOS)
 *													1		Prueba para detectar error de washtdog
 *													2		Secuencia con RTOS y MUTEX
 *													3		Secuencia con RTOS,MUTEX y variables TickType_t
 *
 *VERDION -1 y -2 Pruebas de Alex					-1		Prueba simple de driver para GPIO.
 *													-2		Prueba simple de HAL para GPIO.
*/

#if VERSION == 0
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
//Manda a llamar a la capa BSP 
#include "my_bsp.h"

void app_main(void){
	
    bsp_init();
    bool system_run = false;
    uint8_t cont_color = 0;
    printf("wait button... \n\n");

    while(true){
		
		if(bsp_btn1_pressed()){
			printf("boton 1 pressed\n");
			printf("Starting system...\n\n");
			system_run = true;
			//cont_color = 1;
			bsp_led_state_set();
		}
		else if(bsp_btn2_pressed()){
			printf("boton 2 pressed\n");
			printf("System stop...\n\n");
			bsp_system_stop();
			cont_color = 0; 
			system_run = false;
        }
        
		if(system_run){
			
       		switch(cont_color){
	            case 1: bsp_rgb_set(1,0,0);  break;
	            case 2: bsp_rgb_set(0,1,0);  break;
	            case 3: bsp_rgb_set(0,0,1);  break;
	            default: break;
            }
            
            vTaskDelay(pdMS_TO_TICKS(1000));  
            if(cont_color >3) cont_color =0;
        }
		cont_color ++;
        
        vTaskDelay(pdMS_TO_TICKS(10));
    }    
}



#elif VERSION == 1

#include "my_bsp.h"

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


#elif VERSION == 2

//Manda a llamar a la capa BSP 
#include "my_bsp.h"

 SemaphoreHandle_t mutex_RGB; //Declaración de "semáforo mutex" para proteger variables compartidas entre tareas. 

 bool system_run = false;//bandera de estado de sistema
 uint8_t cont_color = 0;
 
 
void setup(){
	bsp_init();//función de BSP que inicializa Gpios
	mutex_RGB =xSemaphoreCreateMutex();//Crea un mutex (candado) para proteger variables compartidas
    printf("wait button... \n\n");
}


void task_boton(void *pvParameter){
	while(true){
		xSemaphoreTake(mutex_RGB, portMAX_DELAY);//Toma el mutex (lo bloquea). Si otro mutex lo tiene, espera indefinidamente (portMAX_DELAY)
		
		  if(bsp_btn1_pressed()){
			printf("boton 1 pressed\n");
			printf("Starting system...\n\n");
			system_run = true;
			//cont_color = 1;
			
		}
		
		else if(bsp_btn2_pressed()){
			printf("boton 2 pressed\n");
			printf("System stop...\n\n");
           bsp_system_stop();
           cont_color = 0; 
           system_run = false;
            
        }
        xSemaphoreGive(mutex_RGB);//Libera el mutex para que otras tareas puedan acceder a las variables compartidas.
        vTaskDelay(pdMS_TO_TICKS(10));
	}
	
}

void task_state(void *pvParameter){
	while(true){
		if(system_run){
			bsp_led_state_set();
			vTaskDelay(pdMS_TO_TICKS(250));
		}else {
			bsp_system_stop();
			vTaskDelay(pdMS_TO_TICKS(10));
		}
	}
	
}

void task_leds(void *pvParameter){
	while(true)
    { 
		xSemaphoreTake(mutex_RGB, portMAX_DELAY);
		cont_color ++;
		if(system_run){
			
       		switch(cont_color){
	            case 1: bsp_rgb_set(1,0,0);  break;
	            case 2: bsp_rgb_set(0,1,0);  break;
	            case 3: bsp_rgb_set(0,0,1);  break;
	            
            }
            
            vTaskDelay(pdMS_TO_TICKS(1000));   
            if(cont_color >3) cont_color =0;
        }
		
        xSemaphoreGive(mutex_RGB);
        vTaskDelay(pdMS_TO_TICKS(10));
    }    
}

void app_main(void){
	setup();
	
 	xTaskCreate(task_boton, "Botones", 4096, NULL, 2, NULL);
 	xTaskCreate(task_leds, "Led_RGB", 4096, NULL, 1, NULL); 
 	xTaskCreate(task_state, "Led_state", 4096, NULL, 1, NULL);
    
}


#elif VERSION == 3

#include "my_bsp.h"

SemaphoreHandle_t mutex_RGB; //Declaración de "semáforo mutex" para proteger variables compartidas entre tareas. 
bool system_run = false; //bandera de estado de sistema
int cont_color = 0;
TickType_t last_change = 0; //Variable que guarda el momento (en ticks del sistema) para no usar delays bloqueantes.

void setup(){
    bsp_init(); //función de BSP que inicializa Gpios
    mutex_RGB = xSemaphoreCreateMutex(); //Crea un mutex (candado) para proteger variables compartidas
    printf("wait button... \n\n");
}

void task_boton(void *pvParameter){
	
	while(true){
		xSemaphoreTake(mutex_RGB, portMAX_DELAY); //Toma el mutex (lo bloquea). Si otro mutex lo tiene, espera indefinidamente (portMAX_DELAY)
		
		  if(bsp_btn1_pressed()){
			printf("boton 1 pressed\n");
			printf("Starting system...\n\n");
			system_run = true;
			//cont_color = 1;
			last_change = xTaskGetTickCount(); //Guarda el momento actual en ticks 
		}
		
		else if(bsp_btn2_pressed()){
			printf("boton 2 pressed\n");
			printf("System stop...\n\n");
           bsp_system_stop();
           cont_color = 0; 
           system_run = false;
            
        }
        xSemaphoreGive(mutex_RGB); //Libera el mutex para que otras tareas puedan acceder a las variables compartidas.
        vTaskDelay(pdMS_TO_TICKS(10));
	}
	
}

void task_state(void *pvParameter){
 	while(true){
		 xSemaphoreTake(mutex_RGB, portMAX_DELAY);
		if(system_run){
			bsp_led_state_set();
			vTaskDelay(pdMS_TO_TICKS(250));
		}else {
			bsp_system_stop();
			vTaskDelay(pdMS_TO_TICKS(10));
		}
		xSemaphoreGive(mutex_RGB);
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void task_leds(void *pvParameter){
    while(true){ 
		 xSemaphoreTake(mutex_RGB, portMAX_DELAY);
        TickType_t last =last_change; //Copia local del último tiempo de cambio
        
        if(system_run){
            TickType_t now = xTaskGetTickCount(); //Obtiene el tiempo actual en ticks del sistema.
            if((now - last) * portTICK_PERIOD_MS >= 1000){ //Calcula si ha pasado al menos 1 segundo (1000ms) desde el último cambio
                cont_color++;
                if(cont_color > 3) cont_color = 1;

                last_change = now; //Actualiza el tiempo del último cambio con el momento actual.
                
                switch(cont_color){
                    case 1: bsp_rgb_set(1,0,0); printf(" ROJO\n"); break;
                    case 2: bsp_rgb_set(0,1,0); printf(" VERDE\n"); break;
                    case 3: bsp_rgb_set(0,0,1); printf(" AZUL\n"); break;
                }
            }
        }
        xSemaphoreGive(mutex_RGB);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main(void){
    setup();
    //se crean ls tareas
    xTaskCreate(task_boton, "Botones", 2048, NULL, 2, NULL);
    xTaskCreate(task_leds, "Led_RGB", 2048, NULL, 1, NULL); 
    xTaskCreate(task_state, "Led_state", 2048, NULL, 1, NULL);
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
	
	driver_gpio_config_out(LED_BUILTIN, OUTPUTS_INVERTED);
	driver_gpio_config_out(LED_YELLOW, OUTPUTS_INVERTED);
	driver_gpio_config_out(LED_RED, OUTPUTS_INVERTED);
	
	driver_gpio_config_in(BTN_LEFT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	driver_gpio_config_in(BTN_RIGHT, INPUT_PULLUP_MODE, INPUTS_INVERTED);
	
	while(true){
		if(driver_gpio_read(BTN_LEFT) == 0){
			driver_gpio_write(LED_BUILTIN, true);
			driver_gpio_write(LED_YELLOW, true);
			driver_gpio_write(LED_RED, true);
		}
		else{
			driver_gpio_write(LED_BUILTIN, false);
			driver_gpio_write(LED_YELLOW, false);
			driver_gpio_write(LED_RED, false);
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

#include "my_driver.h"
#include "my_hal.h"

//#include "hal_button.h"
//#include "driver_hw_registers_interrupts.h"
//#include "driver_gpio_interrupts.h"




#define LED_BUILTIN	2
#define LED_YELLOW	4
#define LED_RED		5

#define OUTPUTS_INVERTED false

#define BTN_LEFT	18
#define BTN_RIGHT	19

#define INPUTS_INVERTED	true



void app_main(){
	
	//vTaskDelay(pdMS_TO_TICKS(3000));
	printf("Starting system...\n");
	
	driver_gpio_config_out(LED_BUILTIN, OUTPUTS_INVERTED);
	driver_gpio_config_out(LED_YELLOW, OUTPUTS_INVERTED);
	
	
	button_t left_button = {0};
	hal_button_init(
		&left_button, 
		BTN_LEFT, 
		INPUT_PULLUP_MODE, 
		INPUTS_INVERTED
	);
	
	driver_gpio_config_in_intr(
		BTN_RIGHT, 
		INPUT_PULLUP_MODE, 
		FALLING_EDGE, 
		driver_gpio_isr_handler_wrapper
	);
	/*
	timer_init(
		TIMG_0_TIMER_0, 
		8000, 
		true, 
		true, 
		1000000,
		timer_isr_handler_wrapper
	);
	*/
	
	
	
	
	while(true){
		if(hal_button_was_pressed(&left_button)){
			driver_gpio_toggle(LED_BUILTIN);
		}
		
		if(led_test_flag == 1){
			led_test_flag = 0;
			driver_gpio_toggle(LED_BUILTIN);
			printf("Button pressed\n");
		}
		
		if(led_test_flag_timer == 1){
			led_test_flag_timer = 0;
			driver_gpio_toggle(LED_YELLOW);
			printf("Timer interruption. Counter: %llu\n", counted_ticks);
		}
		
		printf("Timer 0 counter: %llu\n", timer_get_counter(TIMG_0_TIMER_0));
		
		vTaskDelay(pdMS_TO_TICKS(100));
	}
	
	return;
}	

#endif /* VERSION */