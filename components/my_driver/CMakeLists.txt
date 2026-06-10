idf_component_register(
	SRCS 
		driver_gpio.c
		driver_gpio_interrupts.c
		driver_timer.c
	INCLUDE_DIRS "include"
	REQUIRES
		driver
)

