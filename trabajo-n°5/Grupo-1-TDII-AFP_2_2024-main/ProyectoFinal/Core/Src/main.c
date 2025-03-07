/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "i2c-lcd.h"
#include "API_GPIO.h"
#include "API_uart.h"
#include "API_debounce.h"
#include "API_delay.h"
#include "API_adc.h"
#include "API_i2c.h"
#include "string.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
// Declaración externa de las variables
extern volatile bool adcConversionComplete; // Declaración externa de la variable
extern volatile uint32_t adcValue; // Variable externa que contiene el valor del ADC
uint8_t cadena;
delay_t miDelay1;
uint8_t bandera1 = 1;
uint8_t bufferaux = 0;
uint8_t uartRxBuffer[16];  // Tamaño ajustable según lo que necesites
uint8_t uartReceivedFlag = 0;  // Flag para indicar recepción completa
uint8_t *receivedData;
uint32_t photoSensorValue = 0; // Valor leído del fotosensor

//delay_t miDelay;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_ADC1_Init();
	MX_I2C1_Init();
	MX_USART2_UART_Init();
	/* USER CODE BEGIN 2 */
	lcd_init();
	//MENSAJE DE VIENVENIDA
	uartSendString((uint8_t*) "Sistema inicializado. Enviá algo por Bluetooth:\n");
	lcd_clear();
	lcd_enviar("cargando", 0, 0);


	HAL_Delay(2000);
	//PARA NO DEJAR LA PANTALLA EN BLANCO
	lcd_clear();
	lcd_enviar("Luz:0  %pwm:   %", 0, 0);
	lcd_enviar("R1:  R2:  R3: ", 1, 0);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */
		/* USER CODE BEGIN 3 */


		//obtenemos valor del pin analogico
		// Inicia el ADC
		HAL_ADC_Start(&hadc1);

		// Espera la conversión
		if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK) {
			photoSensorValue = HAL_ADC_GetValue(&hadc1);
			// Usa el valor adcValue
		}

		// Detén el ADC
		HAL_ADC_Stop(&hadc1);


		// Chequear si hay datos recibidos por UART
		receivedData = uartGetReceivedData();

		//confirmacion de recepcion y comparacion de datos
		if (strlen((char*) receivedData) > 0) {
			uartSendString((uint8_t*) "Recibido: ");
			uartSendString((uint8_t*) receivedData);
			uartSendString((uint8_t*) "\n");

			// Comparar los datos recibidos con los comandos
			if (strcmp((char*) receivedData, "Encender led verde") == 0) {
				writeLedOn_GPIO(LD1_Pin);
			}
			if (strcmp((char*) receivedData, "Encender led rojo") == 0) {
				writeLedOn_GPIO(LD3_Pin);
			}
			if (strcmp((char*) receivedData, "Encender led azul") == 0) {
				writeLedOn_GPIO(LD2_Pin);
			}
			if (strcmp((char*) receivedData, "Apagar led verde") == 0) {
				writeLedOff_GPIO(LD1_Pin);
			}
			if (strcmp((char*) receivedData, "Apagar led rojo") == 0) {
				writeLedOff_GPIO(LD3_Pin);
			}
			if (strcmp((char*) receivedData, "Apagar led azul") == 0) {
				writeLedOff_GPIO(LD2_Pin);
			}
			if (strcmp((char*) receivedData, "RaN") == 0) {
				HAL_GPIO_WritePin(GPIOE, rele1_Pin, GPIO_PIN_RESET);
				uartSendString((uint8_t*) "rele activado");
				lcd_enviar("R1:on", 1, 0);
			}
			if (strcmp((char*) receivedData, "RbN") == 0) {
				HAL_GPIO_WritePin(GPIOE, rele2_Pin, GPIO_PIN_RESET);
				uartSendString((uint8_t*) "rele activado");
				lcd_enviar("R2:on", 1, 5);
			}
			if (strcmp((char*) receivedData, "RcN") == 0) {
				HAL_GPIO_WritePin(GPIOE, rele3_Pin, GPIO_PIN_RESET);
				uartSendString((uint8_t*) "rele activado");
				lcd_enviar("R3:on", 1, 10);
			}
			if (strcmp((char*) receivedData, "RaFF") == 0) {
				uartSendString((uint8_t*) "rele desactivado");
				HAL_GPIO_WritePin(GPIOE, rele1_Pin, GPIO_PIN_SET);
				lcd_enviar("R1:of", 1, 0);
			}
			if (strcmp((char*) receivedData, "RbFF") == 0) {
				uartSendString((uint8_t*) "rele desactivado");
				HAL_GPIO_WritePin(GPIOE, rele2_Pin, GPIO_PIN_SET);
				lcd_enviar("R2:of", 1, 5);
			}
			if (strcmp((char*) receivedData, "RcFF") == 0) {
				uartSendString((uint8_t*) "rele desactivado");
				HAL_GPIO_WritePin(GPIOE, rele3_Pin, GPIO_PIN_SET);
				lcd_enviar("R3:of", 1, 10);
			}
		}

		//formamos mensaje en pantalla

		cadena = 100 - (photoSensorValue / 4095.0) * 100;
		if(abs(cadena - bufferaux) >= 5){
			        sprintf((char*) uartRxBuffer, "Luz:%u  ", cadena);
					//lcd_clear();
					lcd_enviar((char*) uartRxBuffer, 0, 0);
					lcd_enviar((char *)"%", 0, 7);
					uartSendString((uint8_t*) uartRxBuffer);
					uartSendString((uint8_t *)"\n");
					bufferaux=cadena;

		}




		HAL_Delay(500);  // Espera breve para evitar uso excesivo de CPU
	}

	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK) {
		Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
