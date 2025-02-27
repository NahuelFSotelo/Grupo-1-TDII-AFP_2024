/*
 * API_adc.h
 *
 *  Created on               : Jan 11, 2025
 *      Author               : Nahue
 *  Function of driver       : Driver para inicializar y manejar el periférico ADC1 en un microcontrolador STM32.
 */

#ifndef API_INC_API_ADC_H_
#define API_INC_API_ADC_H_

/* Includes ***********************************************************************************/
#include "API_uart.h" // Dependencia para funciones UART, si es necesaria para este driver
#include "stm32f4xx_hal.h"

// Declarar hadc1 como variable externa
extern ADC_HandleTypeDef hadc1;

// Funciones de inicialización
void MX_ADC1_Init(void);

// Funciones de control
void ADC_Start(void);
void ADC_SetChannel(uint32_t channel);
uint32_t ADC_GetValue(void);
bool ADC_IsConversionComplete(void);

#endif /* API_INC_API_ADC_H_ */
