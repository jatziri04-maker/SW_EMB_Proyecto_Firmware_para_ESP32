#ifndef HW_REGISTERS_GPIO_H
#define HW_REGISTERS_GPIO_H

#include <stdint.h>

// **** Secciones del archivo:
// - Registros de hardware usados para la configuración de GPIOs.
// - Bit masks para registros GPIO.
// - Macro funciones para configurar registros GPIO.
// - Otras constantes.





/**************************************************************************/
// **** Registros de hardware usados para la configuración de GPIOs:

#define HWREG32(x) ((volatile uint32_t*)(x))

// Registro - GPIO - Enable:
#define REG_GPIO_ENABLE 	HWREG32(0x3FF44020)


// Registro - GPIO - Registros para configuración de salidas:
#define REG_GPIO_OUT 		HWREG32(0x3FF44004)
#define REG_GPIO_OUT_W1TS	HWREG32(0x3FF44008)
#define REG_GPIO_OUT_W1TC	HWREG32(0x3FF4400C)


// Registro - GPIO - Registros para configuración de entradas:
#define REG_GPIO_IN 		HWREG32(0x3FF4403C) // GPIO 0-31 input registers.
#define REG_GPIO_IN1 		HWREG32(0x3FF44040) // GPIO 32-39 input registers.

#define REG_GPIO_STATUS		HWREG32(0x3FF44044) // GPIO 0-31 interrupt status register.
#define REG_GPIO_STATUS1	HWREG32(0x3FF44050) // GPIO 32-39 interrupt status register.


// **** GPIO - Registros específicos para configuración como entradas:

#define REG_GPIO_PIN_0				HWREG32(0x3FF44088)
#define REG_GPIO_FUNC_0_IN_SEL_CFG 	HWREG32(0x3FF44130)
// Nota: 	Los registros REG_GPIO_PIN_X y REG_GPIO_FUNC_X_IN_SEL_CFG
//			para los demás pines GPIO son contiguos a REG_GPIO_PIN_0 y
//			REG_GPIO_FUNC_0_IN_SEL_CFG y se pueden obtener con:
//			REG_GPIO_PIN_0 + (0x04)*(gpio_num).

#define REG_GPIO_0_IO_MUX	HWREG32(0x3FF49044)
#define REG_GPIO_1_IO_MUX	HWREG32(0x3FF49088)
#define REG_GPIO_2_IO_MUX	HWREG32(0x3FF49040)
#define REG_GPIO_3_IO_MUX	HWREG32(0x3FF49084)
#define REG_GPIO_4_IO_MUX	HWREG32(0x3FF49048)
#define REG_GPIO_5_IO_MUX	HWREG32(0x3FF4906C)
#define REG_GPIO_6_IO_MUX	HWREG32(0x3FF49060)
#define REG_GPIO_7_IO_MUX	HWREG32(0x3FF49064)
#define REG_GPIO_8_IO_MUX	HWREG32(0x3FF49068)
#define REG_GPIO_9_IO_MUX	HWREG32(0x3FF49054)
#define REG_GPIO_10_IO_MUX	HWREG32(0x3FF49058)
#define REG_GPIO_11_IO_MUX	HWREG32(0x3FF4905C)
#define REG_GPIO_12_IO_MUX	HWREG32(0x3FF49034)
#define REG_GPIO_13_IO_MUX	HWREG32(0x3FF49038)
#define REG_GPIO_14_IO_MUX	HWREG32(0x3FF49030)
#define REG_GPIO_15_IO_MUX	HWREG32(0x3FF4903C)
#define REG_GPIO_16_IO_MUX	HWREG32(0x3FF4904C)
#define REG_GPIO_17_IO_MUX	HWREG32(0x3FF49050)
#define REG_GPIO_18_IO_MUX	HWREG32(0x3FF49070)
#define REG_GPIO_19_IO_MUX	HWREG32(0x3FF49074)
#define REG_GPIO_20_IO_MUX	HWREG32(0x3FF49078) // Solo disponible para ESP32-PICO-V3.
#define REG_GPIO_21_IO_MUX	HWREG32(0x3FF4907C)
#define REG_GPIO_22_IO_MUX	HWREG32(0x3FF49080)
#define REG_GPIO_23_IO_MUX	HWREG32(0x3FF4908C)
#define REG_GPIO_25_IO_MUX	HWREG32(0x3FF49024)
#define REG_GPIO_26_IO_MUX	HWREG32(0x3FF49028)
#define REG_GPIO_27_IO_MUX	HWREG32(0x3FF4902C)
#define REG_GPIO_32_IO_MUX	HWREG32(0x3FF4901C)
#define REG_GPIO_33_IO_MUX	HWREG32(0x3FF49020)
#define REG_GPIO_34_IO_MUX	HWREG32(0x3FF49014)
#define REG_GPIO_35_IO_MUX	HWREG32(0x3FF49018)
#define REG_GPIO_36_IO_MUX	HWREG32(0x3FF49004)
#define REG_GPIO_37_IO_MUX	HWREG32(0x3FF49008)
#define REG_GPIO_38_IO_MUX	HWREG32(0x3FF4900C)
#define REG_GPIO_39_IO_MUX	HWREG32(0x3FF49010)

// Registro - GPIOs no disponibles:
#define REG_GPIO_24_IO_MUX	HWREG32(0x00) // Not available.
#define REG_GPIO_28_IO_MUX	HWREG32(0x00) // Not available.
#define REG_GPIO_29_IO_MUX	HWREG32(0x00) // Not available.
#define REG_GPIO_30_IO_MUX	HWREG32(0x00) // Not available.
#define REG_GPIO_31_IO_MUX	HWREG32(0x00) // Not available.

// Registro - Arreglo para registros IO MUX (configuración de entradas):
static volatile uint32_t* const hwreg32_io_mux[] = {
	REG_GPIO_0_IO_MUX,
	REG_GPIO_1_IO_MUX,
	REG_GPIO_2_IO_MUX,
	REG_GPIO_3_IO_MUX,
	REG_GPIO_4_IO_MUX,
	REG_GPIO_5_IO_MUX,
	REG_GPIO_6_IO_MUX,
	REG_GPIO_7_IO_MUX,
	REG_GPIO_8_IO_MUX,
	REG_GPIO_9_IO_MUX,
	REG_GPIO_10_IO_MUX,
	REG_GPIO_11_IO_MUX,
	REG_GPIO_12_IO_MUX,
	REG_GPIO_13_IO_MUX,
	REG_GPIO_14_IO_MUX,
	REG_GPIO_15_IO_MUX,
	REG_GPIO_16_IO_MUX,
	REG_GPIO_17_IO_MUX,
	REG_GPIO_18_IO_MUX,
	REG_GPIO_19_IO_MUX,
	REG_GPIO_20_IO_MUX,
	REG_GPIO_21_IO_MUX,
	REG_GPIO_22_IO_MUX,
	REG_GPIO_23_IO_MUX,
	REG_GPIO_24_IO_MUX,
	REG_GPIO_25_IO_MUX,
	REG_GPIO_26_IO_MUX,
	REG_GPIO_27_IO_MUX,
	REG_GPIO_28_IO_MUX,
	REG_GPIO_29_IO_MUX,
	REG_GPIO_30_IO_MUX,
	REG_GPIO_31_IO_MUX,
	REG_GPIO_32_IO_MUX,
	REG_GPIO_33_IO_MUX,
	REG_GPIO_34_IO_MUX,
	REG_GPIO_35_IO_MUX,
	REG_GPIO_36_IO_MUX,
	REG_GPIO_37_IO_MUX,
	REG_GPIO_38_IO_MUX,
	REG_GPIO_39_IO_MUX,
};




/**************************************************************************/
// **** Bit masks para registros:

// Bit mask - Pines en registros GPIO comúnes (ej.: REG_GPIO_ENABLE):
#define REG_BIT_GPIO_X(gpio_num) (1UL << (gpio_num))

// Bit mask - Bits de los registros IO MUX (entradas):
#define REG_IO_MUX_INPUT_EN_BIT		(1 << 9)	// FUN_IE REG: Input enable of pin: 1 = enabled.
#define REG_IO_MUX_PULL_UP_EN_BIT 	(1 << 8) 	// FUN_WPU REG: 1: internal pull-up enabled.
#define REG_IO_MUX_PULL_DOWN_EN_BIT (1 << 7)	// FUN_WPD REG: 1: internal pull-down enabled.
#define REG_IO_MUX_FUN_DRV_BITS 	(0x3 << 10)	// FUN_DRV REG: 0.
#define REG_IO_MUX_FUN_SEL_BITS		(0x7 << 12) // MCU_SEL REG: 2 GPIO mode.

#define REG_IO_MUX_FUN_DRV_FOR_GPIO	(0x00 << 10)
#define REG_IO_MUX_FUN_SEL_FOR_GPIO	(0x02 << 12)





/**************************************************************************/
// **** Macro funciones:

// Macro - Funciones para validar número de GPIO:
#define VALID_GPIO(gpio_num) \
	((((int8_t)gpio_num) >= 0 	&& (gpio_num) <= 19) || \
	 ((gpio_num) >= 21 	&& (gpio_num) <= 23) || \
	 ((gpio_num) >= 25 	&& (gpio_num) <= 27) || \
	 ((gpio_num) >= 32 	&& (gpio_num) <= 39))
	 
 #define VALID_GPIO_OUTPUT(gpio_num) \
	((((int8_t)gpio_num) >= 0 	&& (gpio_num) <= 19) || \
	 ((gpio_num) >= 21 	&& (gpio_num) <= 23) || \
	 ((gpio_num) >= 25 	&& (gpio_num) <= 27) || \
	 ((gpio_num) >= 32 	&& (gpio_num) <= 33) || \
	 ((gpio_num) >= 37 	&& (gpio_num) <= 38))
// Nota: GPIOs 34, 35, 36 y 39 solo pueden ser usados como entradas.


// Macro - Funciones para poner en 1 o 0 bits específicos en registros:
#define SET_ADDRESS_BITS(address, bits) 	(*HWREG32(address) |= (bits))
#define SET_REG_BITS(hwreg32, bits)			(*(hwreg32) |= (bits))

#define CLEAR_ADDRESS_BITS(address, bits) 	(*HWREG32(address) &= ~(bits))
#define CLEAR_REG_BITS(hwreg32, bits)		(*(hwreg32) &= ~(bits))


// Macro - Funciones para poner en 1 o 0 bits del registro REG_GPIO_ENABLE:
#define SET_GPIO_ENABLE(bits)		(*REG_GPIO_ENABLE |= (bits))
#define CLEAR_GPIO_ENABLE(bits)		(*REG_GPIO_ENABLE &= ~(bits))

#define SET_OUTPUT_ENABLE(bits)		(SET_GPIO_ENABLE(bits))
#define SET_INPUT_ENABLE(bits)		(CLEAR_GPIO_ENABLE(bits))


// Macro - Funciones para poner en 1 o 0 bits del registro REG_GPIO_OUT:
#define SET_OUTPUT(bits)			(*REG_GPIO_OUT |= (bits))
#define CLEAR_OUTPUT(bits)			(*REG_GPIO_OUT &= ~(bits))
#define TOGGLE_OUTPUT(bits)			(*REG_GPIO_OUT ^= (bits))


// Macro - Funciones para leer registros:
#define READ_ADDRESS(address)			(*HWREG32(address))
#define READ_ADDRESS_BIT(address, bit)	(READ_ADDRESS(address) & bit)

#define READ_REG(hwreg32)				(*hwreg32)
#define READ_REG_BIT(hwreg32, bit)		(READ_REG(hwreg32) & bit)

#define READ_INPUT(gpio_num)								\
	(READ_REG_BIT(											\
		((gpio_num <= 31) ? REG_GPIO_IN : REG_GPIO_IN1),	\
		REG_BIT_GPIO_X(gpio_num)							\
	))														\
	
#define READ_OUTPUT(gpio_num)	\
	(READ_REG_BIT(REG_GPIO_OUT, REG_BIT_GPIO_X(gpio_num)))


// Macro - Funciones para obtener la dirección de registros GPIO
// configurados como entradas o con funcionalidad adicional:
#define REG_GPIO_X_IO_MUX(gpio_num) \
	(VALID_GPIO(gpio_num) ? hwreg32_io_mux[(gpio_num)] : 0x00)
	
#define REG_GPIO_PIN_X(gpio_num) \
	(VALID_GPIO(gpio_num) ? (REG_GPIO_PIN_0 + (0x04)*(gpio_num)) : 0x00)

#define REG_GPIO_FUNC_X_IN_SEL_CFG(gpio_num) \
	(VALID_GPIO(gpio_num) ? (REG_GPIO_FUNC_0_IN_SEL_CFG + (0x04)*(gpio_num)) : 0x00)


// Macro - Funciones para configurar función de IO MUX (2: GPIO mode):
#define REG_IO_MUX_X_MCU_SEL(gpio_num, fun) do{	\
		CLEAR_REG_BITS(REG_GPIO_X_IO_MUX(gpio_num), REG_IO_MUX_FUN_SEL_BITS); 	\
		SET_REG_BITS(REG_GPIO_X_IO_MUX(gpio_num), ((fun) << 12));				\
	}while(0)
	 
#define REG_IO_MUX_X_MCU_SEL_GPIO_FUN(gpio_num)	\
	REG_IO_MUX_X_MCU_SEL((gpio_num), 2)




/****************************************************************************/
// **** Otras constantes:

#define INPUT_NO_PULL_MODE	0
#define INPUT_PULLUP_MODE 	1
#define INPUT_PULLDOWN_MODE 2




#endif /* HW_REGISTERS_GPIO_H */