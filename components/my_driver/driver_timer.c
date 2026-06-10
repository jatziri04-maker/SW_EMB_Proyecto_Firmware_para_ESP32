#include <stdint.h>
#include <stdbool.h>

//#include "rom/ets_sys.h"
#include "esp_intr_alloc.h"
#include "soc/interrupts.h"

#include "driver_hw_registers_general.h"
#include "driver_hw_registers_timers.h"
#include "driver_timer.h"




// **** Secciones del archivo:
// - Variables globales.
// - Definición de funciones para configurar timers.




/**************************************************************************/
// **** Variables globales:

uint8_t led_test_flag_timer = 0;
uint64_t counted_ticks = 0;




/**************************************************************************/
// **** Funciones para configurar timers:

// ISR default:
void IRAM_ATTR driver_tmr_isr_handler_wrapper(void *arg){
	
	timer_e timer = (timer_e)(uint32_t)arg;
	
	volatile uint32_t *timer_base_reg	= REG_TIMG_0_T0_BASE;
	volatile uint32_t *timg_base_reg 	= REG_TIMG_0_BASE;
	
	// Se limpia la interrupción:
	WRITE_REG(
		REG_TIMG_N_INT_CLR(timg_base_reg), 
		REG_TIMG_INT_T0_INT_CLR
	);
	
	// Se rehabilita la alarma del timer manualmente:
	SET_REG_BITS(
		REG_TIMER_CONFIG(timer_base_reg), 
		REG_TIMER_CONFIG_ALARM_EN_BIT
	);
	
	// Se fuerza la actualización:
	WRITE_REG(
		REG_TIMER_UPDATE(timer_base_reg), 0x1
	);
	
	// Lee conteo:
	uint64_t lo = READ_REG(
		REG_TIMER_LO(timer_base_reg)
	);
	
	uint64_t hi = READ_REG(
		REG_TIMER_HI(timer_base_reg)
	);
	
	counted_ticks = (hi << 32) | lo;
	
	led_test_flag_timer = 1;
	/*
	timer_e timer = (timer_e)(uint32_t)arg;
	
	volatile uint32_t *timer_base_reg;
	volatile uint32_t *timg_base_reg;
	
	switch(timer){
		case TIMG_0_TIMER_0: 
			timer_base_reg 	= REG_TIMG_0_T0_BASE;
			timg_base_reg	= REG_TIMG_0_BASE;
			break;
		case TIMG_0_TIMER_1: 
			timer_base_reg 	= REG_TIMG_0_T1_BASE;
			timg_base_reg	= REG_TIMG_0_BASE;
			break;
		case TIMG_1_TIMER_0: 
			timer_base_reg 	= REG_TIMG_1_T0_BASE;
			timg_base_reg	= REG_TIMG_1_BASE; 
			break;
		case TIMG_1_TIMER_1: 
			timer_base_reg 	= REG_TIMG_1_T1_BASE; 
			timg_base_reg	= REG_TIMG_1_BASE;
			break;
		
		default:
			return;
	}
	
	// Se limpia la interrupción:
	WRITE_REG(
		REG_TIMG_N_INT_CLR(timg_base_reg), 
		((timer == TIMG_0_TIMER_0 || timer == TIMG_1_TIMER_0) ? REG_TIMG_INT_T0_INT_CLR : 0) |
		((timer == TIMG_0_TIMER_1 || timer == TIMG_1_TIMER_1) ? REG_TIMG_INT_T1_INT_CLR : 0)
	);
	
	// Se rehabilita la alarma del timer manualmente:
	SET_REG_BITS(
		REG_TIMER_CONFIG(timer_base_reg), 
		REG_TIMER_CONFIG_ALARM_EN_BIT
	);
	
	// Se fuerza la actualización:
	WRITE_REG(
		REG_TIMER_UPDATE(timer_base_reg), 0x1
	);
	
	// Lee conteo:
	uint64_t lo = READ_REG(
		REG_TIMER_LO(timer_base_reg)
	);
	
	uint64_t hi = READ_REG(
		REG_TIMER_HI(timer_base_reg)
	);
	
	counted_ticks = (hi << 32) | lo;
	
	led_test_flag_timer = 1;
	*/
	
	/*
    timer_e timer = (timer_e)(uint32_t)arg;
    
    // Get timer group base
    uint32_t timg_base = (timer == TIMG_0_TIMER_0 || timer == TIMG_0_TIMER_1) ? 0x3FF5F000 : 0x3FF60000;
    uint32_t clr_bit = (timer == TIMG_0_TIMER_0 || timer == TIMG_1_TIMER_0) ? (1 << 0) : (1 << 1);
    
    // Clear interrupt - Write 1 to clear
    SET_REG_BITS(HWREG32(timg_base + 0xA4), clr_bit);  // TIMG_INT_CLR_REG
    
    // Re-enable alarm
    SET_REG_BITS(REG_TIMER_CONFIG(timer), REG_TIMER_CONFIG_ALARM_EN_BIT);
    
    // Just set a flag - do nothing else!
    led_test_flag_timer = 1;
    */
	
	return;
}


// Función para inicializar timer:
void driver_timer_init(timer_e timer, uint16_t prescaler, bool incremental, bool self_reload, uint64_t count_of_alarm_triggering, void (*isr_handler_ptr)(void *args)){
	
	volatile uint32_t *timer_base_reg;
	volatile uint32_t *timg_base_reg;
	int intr_source;
	
	switch(timer){
		case TIMG_0_TIMER_0: 
			timer_base_reg 	= REG_TIMG_0_T0_BASE;
			timg_base_reg	= REG_TIMG_0_BASE;
			intr_source		= ETS_TG0_T0_LEVEL_INTR_SOURCE;
			break;
			
		case TIMG_0_TIMER_1: 
			timer_base_reg 	= REG_TIMG_0_T1_BASE;
			timg_base_reg	= REG_TIMG_0_BASE;
			intr_source		= ETS_TG0_T1_LEVEL_INTR_SOURCE;
			break;
			
		case TIMG_1_TIMER_0: 
			timer_base_reg 	= REG_TIMG_1_T0_BASE;
			timg_base_reg	= REG_TIMG_1_BASE; 
			intr_source		= ETS_TG1_T0_LEVEL_INTR_SOURCE;
			break;
			
		case TIMG_1_TIMER_1: 
			timer_base_reg 	= REG_TIMG_1_T1_BASE; 
			timg_base_reg	= REG_TIMG_1_BASE;
			intr_source		= ETS_TG1_T1_LEVEL_INTR_SOURCE;
			break;
		
		default:
			return;
	}
	
	
	// **** Paso 1: Deshabilita el timer:
	
	// Deshabilita el timer:
	CLEAR_REG_BITS(
		REG_TIMER_CONFIG(timer_base_reg), 
		REG_TIMER_CONFIG_EN_BIT
	);
	
	// **** Paso 2: Configura el prescaler, incremento y autorecarga:
	
	// Limpia los bits a configurar:
	WRITE_REG_FIELD(
		REG_TIMER_CONFIG(timer_base_reg),
		(0x3FFFFF << 10), 10, 0x0
	);
	
	// Configura el valor del prescaler:
	WRITE_REG_FIELD(
		REG_TIMER_CONFIG(timer_base_reg),
		REG_TIMER_CONFIG_DIVIDER_MASK, REG_TIMER_CONFIG_DIVIDER_SHIFT, prescaler
	);
	
	// Configura el incremento y autorecarga:
	SET_REG_BITS(
		REG_TIMER_CONFIG(timer_base_reg), 
		(REG_TIMER_CONFIG_INCREASE_BIT 		& incremental) |
		(REG_TIMER_CONFIG_AUTORELOAD_BIT 	& self_reload)
	);
	
	
	// **** Paso 3:
	
	// Se limpian los registros bajo y alto de conteo:
	
	WRITE_REG(
		REG_TIMER_LOADLO(timer_base_reg), 0x0
	);
	
	WRITE_REG(
		REG_TIMER_LOADHI(timer_base_reg), 0x0
	);
	
	// Se escribe cualquier valor para disparar una recarga de contador:
	WRITE_REG(
		REG_TIMER_LOAD(timer_base_reg), 0x1
	);
	
	
	// **** Paso 4: Configuración de la alarma del timer:
	
	// Se configura cada cuanto se dispara (rescpecto al valor del contador):
	WRITE_REG(
		REG_TIMER_ALARMLO(timer_base_reg), 
		(count_of_alarm_triggering & 0xFFFFFFFFULL)
	);
	
	WRITE_REG(
		REG_TIMER_ALARMHI(timer_base_reg),
		(count_of_alarm_triggering >> 32)
	);
	
	// Se habilita la alarma del timer:
	SET_REG_BITS(
		REG_TIMER_CONFIG(timer_base_reg), 
		REG_TIMER_CONFIG_ALARM_EN_BIT
	);
	
	
	// **** Paso 5: Configuración de interrupción:
	
	// Se habilita la interrupción por nivel del timer:
	SET_REG_BITS(
		REG_TIMER_CONFIG(timer_base_reg), 
		REG_TIMER_CONFIG_LEVEL_INT_EN_BIT
	);
	
	// Se habilita la interrupción del timer respecto a su módulo:
	SET_REG_BITS(
		REG_TIMG_N_INT_ENA(timg_base_reg), 
		((timer == TIMG_0_TIMER_0 || timer == TIMG_1_TIMER_0) ? REG_TIMG_INT_T0_INT_ENA : 0) |
		((timer == TIMG_0_TIMER_1 || timer == TIMG_1_TIMER_1) ? REG_TIMG_INT_T1_INT_ENA : 0)
	);
	
	// Se registra la ISR del timer y se termina de configurar su interrupción:
	
	
	esp_intr_alloc(
		intr_source,
		ESP_INTR_FLAG_IRAM,
		isr_handler_ptr,
		(void*)(uint32_t)timer,
		NULL
	);
	
	
	// **** Paso 7: Se habilita el timer:
	
	printf("Timer base: %p\n", timer_base_reg);
	printf("UPDATE reg: %p\n", REG_TIMER_UPDATE(timer_base_reg));
	printf("Expected: %p\n", (void*)((uint32_t)timer_base_reg + 0x0C));
	
	SET_REG_BITS(
		REG_TIMER_CONFIG(timer_base_reg), 
		REG_TIMER_CONFIG_EN_BIT
	);
	
	return;
}


// **** Funciones para leer aspectos del timer:

// Función para leer conteo del timer:
uint64_t driver_timer_get_counter(timer_e timer){
	
	volatile uint32_t *timer_base_reg;
	//volatile uint32_t *timg_base_reg;
	
	switch(timer){
		case TIMG_0_TIMER_0: 
			timer_base_reg 	= REG_TIMG_0_T0_BASE;
			//timg_base_reg	= REG_TIMG_0_BASE;
			break;
		case TIMG_0_TIMER_1: 
			timer_base_reg 	= REG_TIMG_0_T1_BASE;
			//timg_base_reg	= REG_TIMG_0_BASE;
			break;
		case TIMG_1_TIMER_0: 
			timer_base_reg 	= REG_TIMG_1_T0_BASE;
			//timg_base_reg	= REG_TIMG_1_BASE; 
			break;
		case TIMG_1_TIMER_1: 
			timer_base_reg 	= REG_TIMG_1_T1_BASE; 
			//timg_base_reg	= REG_TIMG_1_BASE;
			break;
		
		default:
			return 0;
	}
	
	
	// Se fuerza la actualización:
	WRITE_REG(
		REG_TIMER_UPDATE(timer_base_reg), 0x1
	);
	
	
	// Lee conteo:
	uint64_t lo = READ_REG(
		REG_TIMER_LO(timer_base_reg)
	);
	
	uint64_t hi = READ_REG(
		REG_TIMER_HI(timer_base_reg)
	);
	
	return ((hi << 32) | lo);
}




