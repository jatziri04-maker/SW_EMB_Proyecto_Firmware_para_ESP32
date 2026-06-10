#ifndef MY_TIMER_H
#define MY_TIMER_H

#include <stdint.h>
#include <stdbool.h>

#include "driver_gpio_interrupts.h"
#include "driver_hw_registers_interrupts.h"




// **** Secciones del archivo:
// - Notas.
// - Tipos de datos.
// - Variables globales.
// - Definición de funciones para configurar timers.




/**************************************************************************/
/* **** Notas:
	- La ESP32 tiene 4 timers de propósito general de 64 bits.
	- La ESP32 tiene 2 módulos/generadores de timer, cada uno con 2 timers.
	- En la documentación se emplea la nomenclatura TIMGn_Tx, donde:
		- n = Módulo.
		- x = Timer.
	 
	- * Cada timer tiene un prescaler de 16 bits (2 a 65536).
	- * Cada timer tiene un contador de 64 bits auto-recargable y con
	    capacidad de incremento/decremento.
	- Cada timer emlpea el clock APB (APB_CLK, normalmente 80 MHz) como el 
	  reloj básico.
	
*/




/**************************************************************************/
// **** Tipos de datos:

typedef enum{
	TIMER_GENERATOR_0 = 0,
	TIMER_GENERATOR_1 = 1
} timer_generator_e;

typedef enum{
	TIMG_0_TIMER_0 = 0,
	TIMG_0_TIMER_1 = 1,
	TIMG_1_TIMER_0 = 2,
	TIMG_1_TIMER_1 = 3,
} timer_e;




/**************************************************************************/
// **** Variables globales:

extern uint8_t led_test_flag_timer;
extern uint64_t counted_ticks;


/**************************************************************************/
// **** Funciones para configurar timers:

// ISR default:
void IRAM_ATTR driver_tmr_isr_handler_wrapper(void *arg);

// Función para inicializar timer:
void driver_timer_init(timer_e timer, uint16_t prescaler, bool incremental, bool self_reload, uint64_t count_of_alarm_triggering, void (*isr_handler_ptr)(void *args));

// Funciones para leer aspectos del timer:
uint64_t driver_timer_get_counter(timer_e timer);



#endif /* MY_TIMER_H */
