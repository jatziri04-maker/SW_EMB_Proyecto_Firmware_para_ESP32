#ifndef HW_REGISTERS_TIMERS_H
#define HW_REGISTERS_TIMERS_H

#include <stdint.h>

#include "hw_registers_general_macros.h"

// **** Secciones del archivo:
// - Registros usados para la configuración de timers.




/**************************************************************************/
// **** Registros usados para la configuración de timers.

#define REG_TIMG_0_T0_BASE	HWREG32(0x3FF5F000)
#define REG_TIMG_0_T1_BASE	HWREG32(0x3FF5F024)
#define REG_TIMG_1_T0_BASE	HWREG32(0x3FF60000)
#define REG_TIMG_1_T1_BASE	HWREG32(0x3FF60024)

#define REG_TIMG_0_BASE		REG_TIMG_0_T0_BASE
#define REG_TIMG_1_BASE		REG_TIMG_1_T0_BASE

#define REG_TIMER_CONFIG(TIMG_N_TX_BASE)	(TIMG_N_TX_BASE + 0)
#define REG_TIMER_LO(TIMG_N_TX_BASE)		(TIMG_N_TX_BASE + 1)
#define REG_TIMER_HI(TIMG_N_TX_BASE)		(TIMG_N_TX_BASE + 2)
#define REG_TIMER_UPDATE(TIMG_N_TX_BASE)	(TIMG_N_TX_BASE + 3)
#define REG_TIMER_ALARMLO(TIMG_N_TX_BASE)	(TIMG_N_TX_BASE + 4)
#define REG_TIMER_ALARMHI(TIMG_N_TX_BASE)	(TIMG_N_TX_BASE + 5)
#define REG_TIMER_LOADLO(TIMG_N_TX_BASE)	(TIMG_N_TX_BASE + 6)
#define REG_TIMER_LOADHI(TIMG_N_TX_BASE)	(TIMG_N_TX_BASE + 7)
#define REG_TIMER_LOAD(TIMG_N_TX_BASE)		(TIMG_N_TX_BASE + 8)

#define REG_TIMG_N_INT_ENA(TIMG_N_BASE)	(TIMG_N_BASE + 38)
#define REG_TIMG_N_INT_RAW(TIMG_N_BASE)	(TIMG_N_BASE + 39)
#define REG_TIMG_N_INT_ST(TIMG_N_BASE)	(TIMG_N_BASE + 40)
#define REG_TIMG_N_INT_CLR(TIMG_N_BASE)	(TIMG_N_BASE + 41)




/**************************************************************************/
// **** Bit masks para registros:

// Registros REG_TIMER_CONFIG:

// Bit de habilitación del timer:
#define REG_TIMER_CONFIG_EN_BIT			(1UL << 31)

// Bit para definir dirección de conteo:
#define REG_TIMER_CONFIG_INCREASE_BIT		(1UL << 30)
// REG_T0CONFIG_INCREASE_BIT == 0: Time-base counter decrements.
// REG_T0CONFIG_INCREASE_BIT == 1: Time-base counter increments.

// Bit para recargar automáticamente el timer cuando se dispara una alarma:
#define REG_TIMER_CONFIG_AUTORELOAD_BIT	(1UL << 29)

// Bit field para divisor del timer:
#define REG_TIMER_CONFIG_DIVIDER_MASK		(0x1FFFFC00)
#define REG_TIMER_CONFIG_DIVIDER_SHIFT		(13)
// Opciones comunes para divisor de timer:
#define TIMER_DIVIDER_FOR_40_MHZ	(2)
#define TIMER_DIVIDER_FOR_1_MHZ		(80)
#define TIMER_DIVIDER_FOR_100_KHZ	(800)
#define TIMER_DIVIDER_FOR_10_KHZ	(8000)
#define TIMER_DIVIDER_FOR_2_KHZ		(40000)
#define TIMER_DIVIDER_FOR_FREQ(requested_freq) \
	((80000000UL / (requested_freq) < 0) 		? 1 : \
	 (80000000UL / (requested_freq) > 65536)	? 65536 : \
	 (80000000UL / (requested_freq)))

// Bit para definir si la alarma genera una interrupción tipo transición (edge):
#define REG_TIMER_CONFIG_EDGE_INT_EN_BIT	(1UL << 12)

// Bit para definir si la alarma genera una interrupción tipo nivel (level):
#define REG_TIMER_CONFIG_LEVEL_INT_EN_BIT	(1UL << 11)

// Bit para habilitar alarma. Se limpia automáticamente cuando se dispara una alarma.
#define REG_TIMER_CONFIG_ALARM_EN_BIT		(1UL << 10)




// Registros de REG_TIMG_N_INT_ENA:

// Bit para habilitar la interrupción del timer 0:
#define REG_TIMG_INT_T0_INT_ENA		(1 << 0)

// Bit para habilitar la interrupción del timer 1:
#define REG_TIMG_INT_T1_INT_ENA		(1 << 1)

// Bit para habilitar la interrupción de Watchdog timer:
#define REG_TIMG_INT_WDT_INT_ENA	(1 << 2)



// Registros de REG_TIMG_N_INT_CLR:

// Bit para habilitar la interrupción del timer 0:
#define REG_TIMG_INT_T0_INT_CLR		(1 << 0)

// Bit para habilitar la interrupción del timer 1:
#define REG_TIMG_INT_T1_INT_CLR		(1 << 1)

// Bit para habilitar la interrupción de Watchdog timer:
#define REG_TIMG_INT_WDT_INT_CLR	(1 << 2)




#endif /* HW_REGISTERS_TIMERS_H */
