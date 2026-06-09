#ifndef HW_REGISTERS_INTERRUPTS_H
#define HW_REGISTERS_INTERRUPTS_H

#include <stdint.h>

#include "hw_registers_general_macros.h"

// **** Secciones del archivo:
// - Registros usados para la configuración de GPIOs para interrupciones.




/**************************************************************************/
// **** Registros usados para la configuración de GPIOs para interrupciones.

// Registros de estado de interrupciones (cada bit representa un GPIO):
#define REG_GPIO_STATUS		HWREG32(0x3FF44044) // GPIO 0-31
#define REG_GPIO_STATUS1	HWREG32(0x3FF44050) // GPIO 32-39

#define REG_GPIO_STATUS_W1TC	HWREG32(0x3FF44048)
#define REG_GPIO_STATUS1_W1TC	HWREG32(0x3FF44054)

// Registros para configurar interrupciones (contiguos para cada GPIO):
#define REG_GPIO_PIN_0		HWREG32(0x3FF44088)
#define REG_GPIO_PIN_X(gpio_num) \
	(VALID_GPIO(gpio_num) ? (REG_GPIO_PIN_0 + (gpio_num)) : 0x00)


// Registros específicos para cada procesador:
#define REG_GPIO_ACPU_INT		HWREG32(0x3FF44060) // Read-only
#define REG_GPIO_ACPU_INT1		HWREG32(0x3FF44074) // Read-only
#define REG_GPIO_ACPU_NMI_INT	HWREG32(0x3FF44064) // Read-only
#define REG_GPIO_ACPU_NMI_INT1	HWREG32(0x3FF44078) // Read-only

#define REG_GPIO_PCPU_INT		HWREG32(0x3FF44068) // Read-only
#define REG_GPIO_PCPU_INT1		HWREG32(0x3FF4407C) // Read-only
#define REG_GPIO_PCPU_NMI_INT	HWREG32(0x3FF4406C) // Read-only
#define REG_GPIO_PCPU_NMI_INT1	HWREG32(0x3FF44080) // Read-only




/**************************************************************************/
// **** Registros usados para la configuración de fuentes de interrupción:

#define REG_DPORT_APP_GPIO_INTERRUPT_MAP		HWREG32(0x3FF00270)
#define REG_DPORT_APP_GPIO_INTERRUPT_NMI_MAP	HWREG32(0x3FF00274)

#define REG_DPORT_PRO_GPIO_INTERRUPT_MAP		HWREG32(0x3FF0015C)
#define REG_DPORT_PRO_GPIO_INTERRUPT_NMI_MAP	HWREG32(0x3FF00160)

// Registros de status de interrupción:
// Nota: 	Todos son read-only. El registro de interés para interrupciones
// 			mediante GPIOs es REG_DPORT_APP_INTR_STATUS_0.
#define REG_DPORT_PRO_INTR_STATUS_0	HWREG32(0x3FF000EC)
#define REG_DPORT_PRO_INTR_STATUS_1	HWREG32(0x3FF000F0)
#define REG_DPORT_PRO_INTR_STATUS_2	HWREG32(0x3FF000F4)

#define REG_DPORT_APP_INTR_STATUS_0	HWREG32(0x3FF000F8)
#define REG_DPORT_APP_INTR_STATUS_1	HWREG32(0x3FF000FC)
#define REG_DPORT_APP_INTR_STATUS_2	HWREG32(0x3FF00100)

#define REG_PIDCTRL_INTERRUPT_ENABLE HWREG32(0x3FF1F000)
#define REG_PIDCTRL_INTERRUPT_ADDR_1 HWREG32(0x3FF1F004)
#define REG_PIDCTRL_INTERRUPT_ADDR_2 HWREG32(0x3FF1F008)
#define REG_PIDCTRL_INTERRUPT_ADDR_3 HWREG32(0x3FF1F00C)
#define REG_PIDCTRL_INTERRUPT_ADDR_4 HWREG32(0x3FF1F010)
#define REG_PIDCTRL_INTERRUPT_ADDR_5 HWREG32(0x3FF1F014)
#define REG_PIDCTRL_INTERRUPT_ADDR_6 HWREG32(0x3FF1F018)
#define REG_PIDCTRL_INTERRUPT_ADDR_7 HWREG32(0x3FF1F01C)

/**************************************************************************/
// **** Bit masks para registros:

// Registros REG_GPIO_PIN_X:

// INT_ENA:
#define GPIO_PIN_X_INT_ENA_MASK		(0x03E000)
#define GPIO_PIN_X_INT_ENA_SHIFT	(13)
// Opciones (tipo de habilitación por CPU):
#define INT_ENA_DISABLED	(0x0)
#define INT_ENA_APP_IE		(0x1)
#define INT_ENA_APP_NMIE	(0x2)
#define INT_ENA_PRO_IE		(0x4)
#define INT_ENA_PRO_NMIE	(0x8)

// INT_TYPE:
#define GPIO_PIN_X_INT_TYPE_MASK	(0x0380)
#define GPIO_PIN_X_INT_TYPE_SHIFT	(7)
// Opciones (tipos de disparo):
#define INT_TYPE_DISABLED		(0)
#define INT_TYPE_RISING_EDGE	(1)
#define INT_TYPE_FALLING_EDGE	(2)
#define INT_TYPE_ANY_EDGE		(3)
#define INT_TYPE_LOW_LEVEL		(4)
#define INT_TYPE_HIGH_LEVEL		(5)

// WAKEUP_ENABLE:
#define GPIO_PIN_X_WAKEUP_ENABLE_BIT 	(1UL << 10)

// PAD_DRIVER:
#define GPIO_PIN_X_PAD_DRIVER_BIT 		(1UL << 2)
// 0: Normal output.
// 1: Open drain output.


// Registros de fuentes de interrupción 
// (ej.: REG_DPORT_APP_GPIO_INTERRUPT_MAP):

// DPORT_APP_X_MAP:
#define DPORT_CPU_X_MAP_MASK	(0x1F)
#define DPORT_CPU_X_MAP_SHIFT	(0)
// Opciones de interés:
#define PERIPHERAL_EDGE_INTR_PRIORITY_1 (10)
#define PERIPHERAL_EDGE_INTR_PRIORITY_3 (22)
#define PERIPHERAL_EDGE_INTR_PRIORITY_4 (28)






/**************************************************************************/
// **** Macro funciones:

// Función para leer registros REG_GPIO_STATUS y REG_GPIO_STATUS1:
#define READ_GPIO_STATUS(gpio_num) \
	(READ_REG_BIT( \
		((gpio_num <= 31) ? REG_GPIO_STATUS : REG_GPIO_STATUS1), \
		((gpio_num <= 31) ? REG_BIT_GPIO_X(gpio_num) : REG_BIT_GPIO_X(gpio_num - 32)) \

#define SET_GPIO_PIN_X_FOR_NEG_EDGE_INTR(gpio_num) do{ \
		WRITE_REG_FIELD( \
			REG_GPIO_PIN_X(gpio_num), \
			GPIO_PIN_X_INT_ENA_MASK, GPIO_PIN_X_INT_ENA_SHIFT, INT_ENA_APP_IE \
		); \
		WRITE_REG_FIELD( \
			REG_GPIO_PIN_X(gpio_num), \
			GPIO_PIN_X_INT_TYPE_MASK, GPIO_PIN_X_INT_TYPE_SHIFT, INT_TYPE_FALLING_EDGE \
		); \
		CLEAR_REG_BITS( \
			REG_GPIO_PIN_X(gpio_num), \
			GPIO_PIN_X_WAKEUP_ENABLE_BIT | GPIO_PIN_X_PAD_DRIVER_BIT \
		); \
	}while(0)
	
#define SET_GPIO_PIN_X_FOR_DISABLED_INTR(gpio_num) do{ \
		WRITE_REG_FIELD( \
			REG_GPIO_PIN_X(gpio_num), \
			GPIO_PIN_X_INT_ENA_MASK, GPIO_PIN_X_INT_ENA_SHIFT, INT_ENA_DISABLED \
		); \
		WRITE_REG_FIELD( \
			REG_GPIO_PIN_X(gpio_num), \
			GPIO_PIN_X_INT_TYPE_MASK, GPIO_PIN_X_INT_TYPE_SHIFT, INT_TYPE_DISABLED \
		); \
		CLEAR_REG_BITS( \
			REG_GPIO_PIN_X(gpio_num), \
			GPIO_PIN_X_WAKEUP_ENABLE_BIT | GPIO_PIN_X_PAD_DRIVER_BIT \
		); \
	}while(0)
	



/**************************************************************************/
// **** Macros especiales:

// Fuerza a que el código se localice en IRAM en vez de FLASH:

#define IRAM_ATTR _SECTION_ATTR_IMPL(".iram1", __COUNTER__)

#define _SECTION_ATTR_IMPL(SECTION, COUNTER) __attribute__((section(SECTION "." _COUNTER_STRINGIFY(COUNTER))))

#define _COUNTER_STRINGIFY(COUNTER) #COUNTER




#endif /* HW_REGISTERS_INTERRUPTS_H */
