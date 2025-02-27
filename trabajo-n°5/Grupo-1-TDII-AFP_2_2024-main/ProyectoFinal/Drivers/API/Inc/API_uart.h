/*
 * API_uart.h
 *
 *  Created on               : Nov 30, 2024
 *      Author               : Nahue
 *  Function of driver       : Driver para inicializar y manejar la comunicación UART en un microcontrolador STM32,
 *                             incluyendo funciones para enviar y recibir cadenas de texto.
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

/* Includes ***********************************************************************************/
#include "main.h"      // Cabecera principal del proyecto, necesaria para configuraciones generales
#include <stdbool.h>   // Proporciona el tipo booleano para las funciones del driver

/* Exported Types *****************************************************************************/
// Tamaño máximo del buffer de recepción
#define UART_RX_BUFFER_SIZE 100
// No se especifican tipos exportados adicionales en este archivo
/* Exported Functions Prototypes *************************************************************/
///**
// * @brief Muestra la configuración actual de la UART.
// */
//void showConfigUART(void);

/**
 * @brief Inicializa la UART.
 * @return `true` si la inicialización es exitosa, `false` en caso contrario.
 */
bool uartInit(void);

/**
 * @brief Envía una cadena de texto a través de la UART.
 * @param pstring Puntero a la cadena de texto que se enviará.
 */
void uartSendString(uint8_t *pstring);

/**
 * @brief Envía una cadena de texto de tamaño específico a través de la UART.
 * @param pstring Puntero a la cadena de texto que se enviará.
 * @param size Tamaño de la cadena en bytes.
 */
void uartSendStringSize(uint8_t *pstring, uint16_t size);

/**
 * @brief Recibe una cadena de texto a través de la UART.
 * @param pstring Puntero donde se almacenará la cadena recibida.
 * @param size Tamaño máximo de la cadena a recibir.
 */
void uartReceiveString(uint8_t *pstring, uint16_t size);

/**
 * @brief Inicializa el periférico USART2 para la comunicación UART.
 */
void MX_USART2_UART_Init(void);

/* Nota: La función `MX_USART2_UART_Init` fue comentada en el código original y no se incluye como prototipo. */

void uartReceiveCallback(void);
uint8_t *uartGetReceivedData(void);
#endif /* API_INC_API_UART_H_ */
