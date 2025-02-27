/*
 * API_adc.c
 *
 *  Created on: Jan 11, 2025
 *      Author: Nahue
 */

// Includes privados
#include "API_adc.h"
#include "string.h"
#include "main.h"
#include "stm32f4xx_hal.h"  // Asegúrate de incluir esta cabecera.

// Variables privadas
static volatile uint32_t adcValue = 0;  // Variable para almacenar el valor ADC
 volatile bool adcConversionComplete = false;  // Bandera de conversión completa

// Declaración externa del handler ADC
 ADC_HandleTypeDef hadc1;

/* -----------------------------------------------
 * Funciones de inicialización
 * -----------------------------------------------
 */

/**
 * @brief Inicialización del ADC1.
 * @note Configura el ADC con un solo canal y habilita las interrupciones.
 */
void MX_ADC1_Init(void) {
    ADC_ChannelConfTypeDef sConfig = {0};

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ScanConvMode = DISABLE;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
      if (HAL_ADC_Init(&hadc1) != HAL_OK)

    if (HAL_ADC_Init(&hadc1) != HAL_OK) {
        Error_Handler();
    }

    // Configuración del canal del ADC
    sConfig.Channel = ADC_CHANNEL_0;  // Ejemplo de canal
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
        Error_Handler();
    }
}

/* -----------------------------------------------
 * Funciones de control del ADC
 * -----------------------------------------------
 */

/**
 * @brief Inicia la conversión del ADC en modo interrupción.
 */
void ADC_Start(void) {
    adcConversionComplete = false;  // Reinicia la bandera
    if (HAL_ADC_Start_IT(&hadc1) != HAL_OK) {
        Error_Handler();
    }
}

/**
 * @brief Cambia el canal del ADC.
 * @param channel Canal a configurar.
 */
void ADC_SetChannel(uint32_t channel) {
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
        Error_Handler();
    }
}


/**
 * @brief Verifica si la conversión ha finalizado.
 * @return true si la conversión está completa, false de lo contrario.
 */
bool ADC_IsConversionComplete(void) {
    return adcConversionComplete;
}

/* -----------------------------------------------
 * Callback del ADC
 * -----------------------------------------------
 */

/**
 * @brief Callback de conversión completa del ADC.
 * @param hadc Handler del ADC que generó la interrupción.
 */
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc1) {
    if (hadc1->Instance == ADC1) {
        adcValue = HAL_ADC_GetValue(hadc1);  // Obtiene el valor de conversión
        adcConversionComplete = true;      // Marca la conversión como completa
        if (HAL_ADC_Start_IT(hadc1) != HAL_OK) {
            Error_Handler();               // Si falla, maneja el error
        }
    }
}
/**
 * @brief Retorna el valor leído del ADC.
 * @return Valor ADC (12 bits).
 */
uint32_t ADC_GetValue(void) {
    return adcValue;
}

