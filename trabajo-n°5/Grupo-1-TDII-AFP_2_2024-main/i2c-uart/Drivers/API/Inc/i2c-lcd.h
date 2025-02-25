/*
 * lcd_driver.h
 *
 *  Created on               : Jan 11, 2025
 *      Author               : Nahue
 *  Function of driver       : Driver para manejar un display LCD utilizando la HAL de STM32.
 *                             Incluye funciones para inicializar el LCD, enviar comandos, datos y cadenas de texto.
 */

#ifndef LCD_DRIVER_H_
#define LCD_DRIVER_H_

/* Includes ***********************************************************************************/
#include "stm32f4xx_hal.h" // Librería HAL para microcontroladores STM32 F4xx

/* Exported Functions Prototypes *************************************************************/
/**
 * @brief Inicializa el LCD.
 *        Configura el periférico necesario para comunicar con el display.
 */
void lcd_init(void);

/**
 * @brief Envía un comando al LCD.
 * @param cmd Comando a enviar al LCD.
 */
void lcd_send_cmd(char cmd);

/**
 * @brief Envía un dato al LCD.
 * @param data Dato a enviar al LCD.
 */
void lcd_send_data(char data);

/**
 * @brief Envía una cadena de texto a una posición específica del LCD.
 * @param string Puntero a la cadena de texto a enviar.
 * @param row Fila del LCD donde colocar el texto (0 o 1).
 * @param col Columna del LCD donde colocar el texto (0-15).
 */
void lcd_enviar(char *string, int row, int col);

/**
 * @brief Envía una cadena de texto al LCD desde la posición actual del cursor.
 * @param str Puntero a la cadena de texto a enviar.
 */
void lcd_send_string(char *str);

/**
 * @brief Posiciona el cursor en una ubicación específica del LCD.
 * @param row Fila del LCD (0 o 1).
 * @param col Columna del LCD (0-15).
 */
void lcd_put_cur(int row, int col);

/**
 * @brief Limpia la pantalla del LCD.
 */
void lcd_clear(void);

#endif /* LCD_DRIVER_H_ */
