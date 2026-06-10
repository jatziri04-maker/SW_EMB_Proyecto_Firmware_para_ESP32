idf_component_register(
	SRCS 
		hal_gpio.c 
		hal_button.c
	INCLUDE_DIRS "include"
	REQUIRES 
		my_driver 
		esp_timer
)

