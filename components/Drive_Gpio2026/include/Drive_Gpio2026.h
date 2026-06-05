/*									CAPA DRIVER: 
		VOID GPIO_INIT2026(VOID) PARA ESP32
		funciones a incluir:
		 
		 	void gpio_init2026(void); configura todos los gpios llama a config_in y config_out
		 	void gpi_config_in(pin,pull_mode);
		 	void gpio_config_out(pin, value);
		 	bool gpio_read(pin);
		 	void gpio_write(pin);
*/
#ifndef DRIVE_GPIO_2026_H
#define DRIVE_GPIO_2026_H

#include <stdio.h>
#include <stdbool.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

/* ── Registros GPIO ─────────────────────────────────────────── */
#define GPIO_ENABLE     (*(volatile uint32_t*)0x3FF44020)
#define GPIO_OUT        (*(volatile uint32_t*)0x3FF44004)
#define GPIO_OUT_W1TS   (*(volatile uint32_t*)0x3FF44008)
#define GPIO_OUT_W1TC   (*(volatile uint32_t*)0x3FF4400C)
#define GPIO_IN         (*(volatile uint32_t*)0x3FF4403C)

/* ── Registros IO_MUX ───────────────────────────────────────── */
#define IO_MUX_GPIO18_REG (*(volatile uint32_t*)0x3FF49070) // BTN1
#define IO_MUX_GPIO19_REG (*(volatile uint32_t*)0x3FF49074) // BTN2
#define IO_MUX_GPIO12_REG (*(volatile uint32_t*)0x3FF49034) // R
#define IO_MUX_GPIO13_REG (*(volatile uint32_t*)0x3FF49038) // G
#define IO_MUX_GPIO14_REG (*(volatile uint32_t*)0x3FF49030) // B
#define IO_MUX_GPIO5_REG (*(volatile uint32_t*)0x3FF4906C) 
#define IO_MUX_GPIO2_REG (*(volatile uint32_t*)0x3FF49040)
#define IO_MUX_GPIO4_REG (*(volatile uint32_t*)0x3FF49048)
#define IO_MUX_GPIO16_REG (*(volatile uint32_t*)0x3FF4904C) 
#define IO_MUX_GPIO17_REG (*(volatile uint32_t*)0x3FF49050)

/* ── Bits de configuración IO_MUX ──────────────────────────── */
#define FUN_IE      (1 << 9)   // Input enable
#define PULL_WPD    (1 << 7)   // Pull-down enable
#define PULL_WPU    (1 << 8)   // Pull-up enable

/* ── Máscaras de pines ──────────────────────────────────────── */
#define PIN_BIT18   (1 << 18)  // BTN1
#define PIN_BIT19   (1 << 19)  // BTN2
#define PIN_BIT12   (1 << 12)  // RGB - Verde
#define PIN_BIT13   (1 << 13)  // RGB - Rojo
#define PIN_BIT14   (1 << 14)  // RGB - Azul
#define PIN_BIT4	(1 << 4)   // LEDS DE LA PANTHER
#define PIN_BIT5 	(1 << 5)   //0x20
#define PIN_BIT2 	(1 << 2) 
#define PIN_BIT16 	(1 << 16) 
#define PIN_BIT17 	(1 << 17)

/* ───────── RGB ────────────── */
#define RGB_ALL     (PIN_BIT12 | PIN_BIT13 | PIN_BIT14)

#define DEBOUNCE_MS  50
#define COLOR_MS    1000

/* ───────── Prototipos ─────────────────────────────────────────────── */
void j_gpio_init2026(void);
void j_gpio_config_in(volatile uint32_t *pin, uint32_t bit, uint32_t pull_mode);
void j_gpio_config_out(volatile uint32_t *pin, uint32_t bit);
bool j_gpio_read(uint32_t pin_bit);
void j_gpio_write(uint32_t pin_bit, int on_off);
void rgb_set(int r, int g, int b);   // simplifica la secuencia

#endif
