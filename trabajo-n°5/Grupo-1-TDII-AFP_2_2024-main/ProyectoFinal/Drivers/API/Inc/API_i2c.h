/*
 * API_i2c.h
 *
 *  Created on               : Jan 10, 2025
 *      Author               : Nahue
 *  Function of driver       : Driver para inicializar y manejar el periférico I2C1 en un microcontrolador STM32.
 */

#ifndef API_INC_API_I2C_H_
#define API_INC_API_I2C_H_

/* Includes ***********************************************************************************/
// No se especifican dependencias adicionales en este archivo.

/* Exported Functions Prototypes *************************************************************/
/**
 * @brief Inicializa el periférico I2C1.
 *        Configura y habilita el controlador I2C para comunicación con dispositivos esclavos.
 */
void MX_I2C1_Init(void);


#endif /* API_INC_API_I2C_H_ */
