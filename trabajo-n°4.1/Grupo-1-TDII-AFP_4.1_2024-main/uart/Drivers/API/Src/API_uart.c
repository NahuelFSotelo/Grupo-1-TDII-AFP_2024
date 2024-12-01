/*
 * API_uart.c
 *
 *  Created on: Nov 30, 2024
 *      Author: Nahue
 */

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
#include "API_uart.h"
#include "main.h"
#include <stdio.h>

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */
/* Private function prototypes -----------------------------------------------*/
//void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
void uartSendConfig(UART_InitTypeDef *config) {
	char configMsg[300];

	// Construir mensaje con desplazamiento de puntero en cada salto
	snprintf(configMsg, sizeof(configMsg),
			"        UART Configuración:\n"  // 8 espacios al inicio
					"        -----------------------------------\n"
					"        %-15s : %lu\n"
					"        %-15s : %s\n"
					"        %-15s : %s\n"
					"        %-15s : %s\n"
					"        %-15s : %s\n"
					"        %-15s : %s\n"
					"        %-15s : %s\n", "BaudRate", config->BaudRate,
			"WordLength",
			(config->WordLength == UART_WORDLENGTH_8B) ? "8 bits" : "9 bits",
			"StopBits",
			(config->StopBits == UART_STOPBITS_1) ? "1 bit" : "2 bits",
			"Parity",
			(config->Parity == UART_PARITY_NONE) ? "None" :
			(config->Parity == UART_PARITY_EVEN) ? "Even" : "Odd", "Mode",
			(config->Mode == UART_MODE_TX_RX) ? "TX/RX" :
			(config->Mode == UART_MODE_TX) ? "TX Only" : "RX Only", "HwFlowCtl",
			(config->HwFlowCtl == UART_HWCONTROL_NONE) ? "None" :
			(config->HwFlowCtl == UART_HWCONTROL_RTS) ? "RTS" :
			(config->HwFlowCtl == UART_HWCONTROL_CTS) ? "CTS" : "RTS/CTS",
			"OverSampling",
			(config->OverSampling == UART_OVERSAMPLING_16) ? "16" : "8");

	// Enviar mensaje
	uartSendString((uint8_t*) configMsg);
}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
void MX_USART3_UART_Init(void) {

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */
	// Enviar el mensaje usando uartSendString
	uartSendConfig(&huart3.Init);
	/* USER CODE END USART3_Init 2 */

}
void uartSendString(uint8_t *pstring) {
	uint16_t length = 0;
	// Enviar la cadena hasta encontrar el fin de la cadena ('\0')
	while (pstring[length] != '\0') {
		HAL_UART_Transmit(&huart3, &pstring[length], 1, HAL_MAX_DELAY);
		length++;
	}
}
void uartSendStringSize(uint8_t *pstring, uint16_t size) {
	uint16_t length = 0;
	// Enviar caracteres hasta el tamaño especificado
	while (length < size) {
		HAL_UART_Transmit(&huart3, &pstring[length], 1, HAL_MAX_DELAY);
		length++;
	}
}
void uartReceiveStringSize(uint8_t *pstring, uint16_t size) {
	uint16_t length = 0;
	// Recibir caracteres hasta el tamaño especificado
	while (length < size) {
		HAL_UART_Receive(&huart3, &pstring[length], 1, HAL_MAX_DELAY);
		length++;
	}
}
