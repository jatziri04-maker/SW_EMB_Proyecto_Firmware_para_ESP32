# Firmware diseñado por nivel de capas para la ESP32-PANTHER48



##### **Descripción**

Se desarrolló un firmware modular para el ESP32 que controla un LED RGB (ánodo o cátodo común) mediante dos botones push, aplicando una arquitectura de software por capas (Driver, BSP, HAL) y utilizando Git con un flujo de trabajo basado en ramas y Pull Requests para gestionar el versionamiento de código.



###### **Diseño de la arquitectura por capas**

El firmware se estructuró siguiendo una arquitectura por capas, lo que permite una clara separación de responsabilidades, facilita el mantenimiento y la portabilidad del código. A continuación se describe cada una de las capas implementadas, desde el nivel más bajo (hardware) hasta el nivel más alto (aplicación).

* **Capa Drivers:** lógica de control del LED RGB (encender/apagar colores) y lectura con debounce de botones a nivel de registros.
* **Capa HAL:** funciones de bajo nivel para configurar GPIO (entrada/salida, interrupciones y timer).
* **Capa BSP:** mapeo de pines específicos del hardware (LED\_RED = GPIO13, LED\_GREEN = GPIO12, LED\_BLUE = GPIO14, BUTTON1 = GPIO18, BUTTON2 = GPIO19).
* **Capa Aplicación:** Sistema que activa una secuencia de colores según la combinación de botones.



Este proyecto: "Firmware para ESP32 con arquitectura por capas y control de versiones con Git", es una experiencia formativa completa que integra conceptos teóricos (arquitectura de software embebido, sistemas de control de versiones) con prácticas concretas de desarrollo (programación de registros de hardware, implementación de HAL, gestión de ramas y PRs). Resulta en un firmware funcional, bien estructurado y documentado, que sienta una base sólida para proyectos más complejos en el ámbito de Internet de las Cosas (IoT), robótica y automatización.



**Autores:**

* Jatziri Romero (22061040)
* Abdiel Rodríguez (22061055)

