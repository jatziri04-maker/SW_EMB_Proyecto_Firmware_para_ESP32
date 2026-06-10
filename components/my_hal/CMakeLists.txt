idf_component_register(
	SRCS 
		hal_gpio.c 
		hal_button.c
		hal_led.c
	INCLUDE_DIRS "include"
	REQUIRES 
		my_driver 
		esp_timer
)

