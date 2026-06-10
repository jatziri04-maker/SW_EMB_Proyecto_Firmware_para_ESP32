/**
 * CAPA DRIVER
 * \b Description: Archivo driver_hw_registers_general.h donde se definen macro funciones para manipular y leer registros.
 *
 * @author Jatziri Dennise Romero Bustillos y Abdiel Alejandro Rodríguez Coronado
*/

#ifndef HW_REGISTERS_GENERAL_MACROS_H
#define HW_REGISTERS_GENERAL_MACROS_H

#include <stdint.h>

// **** Secciones del archivo:
// - Macros de uso general para manipulación de registros.




/**************************************************************************/
// **** Macros para manipulación de registros:

#define HWREG32(x) ((volatile uint32_t*)(x))

// Bit mask - Pines en registros GPIO comúnes (ej.: REG_GPIO_ENABLE):
#define REG_BIT_GPIO_X(gpio_num) (1UL << (gpio_num))

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
	 ((gpio_num) >= 32 	&& (gpio_num) <= 33))
// Nota: GPIOs 34, 35, 36 y 39 solo pueden ser usados como entradas.

// Macro - Funciones para poner en 1 o 0 bits específicos en registros:
#define SET_ADDRESS_BITS(address, bits) 	(*HWREG32(address) |= (bits))
#define SET_REG_BITS(hwreg32, bits)			(*(hwreg32) |= (bits))

#define CLEAR_ADDRESS_BITS(address, bits) 	(*HWREG32(address) &= ~(bits))
#define CLEAR_REG_BITS(hwreg32, bits)		(*(hwreg32) &= ~(bits))

// Macro - Funciones para leer registros:
#define READ_ADDRESS(address)			(*HWREG32(address))
#define READ_ADDRESS_BIT(address, bit)	(READ_ADDRESS(address) & bit)

#define READ_REG(hwreg32)				(*hwreg32)
#define READ_REG_BIT(hwreg32, bit)		((READ_REG(hwreg32) & bit) != 0)

// Macro - Funciones para manipular campos de bits:
// 		Example: Set bits 4-7 (mask = 0xF0) to value 0x5:
//		SET_FIELD(reg_value, 0xF0, 0x50);

#define WRITE_REG_FIELD(hwreg32, mask, mask_shift, value) \
    ((*hwreg32) = ((*hwreg32) & ~(mask)) | ((value << mask_shift) & (mask)))

#define WRITE_REG(hwreg32, value) \
	((*hwreg32) = (value))


#endif /* HW_REGISTERS_GENERAL_MACROS_H */
