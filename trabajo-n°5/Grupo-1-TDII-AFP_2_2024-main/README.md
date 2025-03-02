# Sistema de Control Remoto de Actuadores con Monitoreo Ambiental

## Descripción

Este proyecto consiste en un sistema embebido desarrollado sobre una placa **NUCLEO-STM32F429**, capaz de monitorear el nivel de luz ambiente, controlar LEDs y relés mediante comandos Bluetooth, y mostrar información en un display LCD I2C.

El sistema incluye:

- Medición de luz ambiente mediante un sensor LDR y el ADC del STM32.
- Control remoto de LEDs de distintos colores y relés mediante comandos recibidos por Bluetooth.
- Visualización de la luz ambiente y el estado de los relés en un LCD 16x2.
- Confirmación de comandos recibidos mediante comunicación UART.

## Hardware Utilizado

- **NUCLEO-STM32F429**
- **Módulo Bluetooth HC-05**
- **Módulo de 4 relés con optoacoplador**
- **Sensor LDR (GL5528)**
- **Pantalla LCD 16x2 con interfaz I2C**
- **Fuente de 5V**

## Estructura del Software

El código se organiza de forma modular en distintas APIs:

- `API_adc`: Manejo del sensor de luz (ADC).
- `API_uart`: Comunicación con el módulo Bluetooth (UART).
- `API_i2c`: Manejo de la pantalla LCD (I2C).
- `API_GPIO`: Control de LEDs y relés (GPIO).

## Funcionamiento

1. El sistema lee el nivel de luz ambiente y lo muestra en la pantalla LCD.
2. Por Bluetooth, el usuario puede enviar comandos para encender o apagar LEDs y relés.
3. El sistema responde confirmando cada comando recibido.
4. Si la luz ambiente cambia más de un 5%, el nuevo valor se actualiza en el LCD.

## Comandos Bluetooth

Algunos comandos de ejemplo:

- `Encender led rojo`
- `Apagar led verde`
- `Activar rele 1`
- `Desactivar rele 2`

## Periféricos Utilizados

- **GPIO:** Control de LEDs y relés.
- **ADC:** Lectura del sensor LDR.
- **I2C:** Comunicación con la pantalla LCD.
- **UART:** Comunicación con el módulo Bluetooth.

## Buenas Prácticas Aplicadas

- Código modular y fácil de mantener.
- Separación de lógica por periféricos.
- Actualización eficiente de pantalla (solo ante cambios relevantes).
- Confirmación de comandos por UART.
- Uso de la HAL de STM32 para compatibilidad.

## Repositorio

Repositorio oficial del proyecto:  
🔗 [https://github.com/NahuelFSotelo/Grupo-1-TDII-AFP_2024](https://github.com/NahuelFSotelo/Grupo-1-TDII-AFP_2024)

## Créditos

**Grupo N°5 - Técnicas Digitales II - Año 2024**  
- Fernando Nahuel Sotelo  
- Daniel Aragón  
- Nahuel Enrique Beltrán  
- José Gareca  
- Profesor: Ing. Rubén Darío Mansilla  
- ATTP: Ing. Lucas Abdala


