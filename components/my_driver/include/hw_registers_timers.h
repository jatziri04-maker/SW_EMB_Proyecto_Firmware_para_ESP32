#ifndef HW_REGISTERS_TIMERS_H
#define HW_REGISTERS_TIMERS_H

#include <stdint.h>

#include "hw_registers_general_macros.h"

// **** Secciones del archivo:
// - Registros usados para la configuración de timers.




/**************************************************************************/
// **** Registros usados para la configuración de timers.

#define REG_TIMG_0_BASE	HWREG32(0x3FF5F000)
#define REG_TIMG_1_BASE	HWREG32(0x3FF60000)

#define REG_TX_CONFIG(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 0)
#define REG_TX_LO(TIMG_X_BASE)		HWREG32(TIMG_X_BASE + 1)
#define REG_TX_HI(TIMG_X_BASE)		HWREG32(TIMG_X_BASE + 2)
#define REG_TX_UPDATE(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 3)
#define REG_TX_ALARMLO(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 4)
#define REG_TX_ALARMHI(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 5)
#define REG_TX_LOADLO(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 6)
#define REG_TX_LOADHI(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 7)
#define REG_TX_LOAD(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 8)

#define REG_TIMG_X_INT_ENA(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 38)
#define REG_TIMG_X_INT_RAW(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 39)
#define REG_TIM0_X_INT_ST(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 40)
#define REG_TIMG_X_INT_CLR(TIMG_X_BASE)	HWREG32(TIMG_X_BASE + 41)




/**************************************************************************/
// **** Bit masks para registros:

// Registros T0CONFIG:

// Bit de habilitación del timer:
#define REG_TX_CONFIG_EN_BIT			(1UL << 31)

// Bit para definir dirección de conteo:
#define REG_TX_CONFIG_INCREASE_BIT		(1UL << 30)
// REG_T0CONFIG_INCREASE_BIT == 0: Time-base counter decrements.
// REG_T0CONFIG_INCREASE_BIT == 1: Time-base counter increments.

// Bit para recargar automáticamente el timer cuando se dispara una alarma:
#define REG_TX_CONFIG_AUTORELOAD_BIT	(1UL << 29)

// Bit field para divisor del timer:
#define REG_TX_CONFIG_DIVIDER_MASK		(0x1FFFFC00)
#define REG_TX_CONFIG_DIVIDER_SHIFT		(13)
// Opciones comunes para divisor de timer:
// ...

// Bit para definir si la alarma genera una interrupción tipo transición (edge):
#define REG_TX_CONFIG_EDGE_INT_EN_BIT	(1UL << 12)

// Bit para definir si la alarma genera una interrupción tipo nivel (level):
#define REG_TX_CONFIG_LEVEL_INT_EN_BIT	(1UL << 11)

// Bit para habilitar alarma. Se limpia automáticamente cuando se dispara una alarma.
#define REG_TX_CONFIG_ALARM_EN_BIT		(1UL << 10)



#endif /* HW_REGISTERS_TIMERS_H */
