/*
 * API_uart.h
 *
 *  Created on: Nov 30, 2024
 *      Author: Nahue
 */

#ifndef API_INC_API_UART_H_
#define API_INC_API_UART_H_

/* Includes ---------------------------------------------------------*/
#include "main.h"
#include <stdbool.h>

/* Exported types -------------------------------------------------*/
/* Declaración de prototipo de funciones ---------------------------*/
/* void MX_USART3_UART_Init(void); */
void showConfigUART(void);
bool uartInit(void);
void uartSendString(uint8_t *pstring);
void uartSendStringSize(uint8_t *pstring, uint16_t size);
void uartReceiveString(uint8_t *pstring, uint16_t size);
void MX_USART3_UART_Init(void);
void uartSendConfig(UART_InitTypeDef *config);

#endif /* API_INC_API_UART_H_ */

