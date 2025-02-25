/*
 * API_delay.h
 *
 *  Created on: Jan 10, 2025
 *      Author: Nahue
 */

#ifndef API_INC_API_DELAY_H_
#define API_INC_API_DELAY_H_
/*includes*************************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include "stdio.h"
/*Exported types*******************************************************************************/
 typedef struct {
     delay_gpio_t startTime;          // Tiempo de inicio en milisegundos
     delay_gpio_t espera;             // Tiempo de espera en milisegundos
     bool_t corriendo;                // Bandera que indica si el delay está corriendo
 } delay_t;


 /*Exported functions prototypes **************************************************************/
 void DelayGPIO_Iniciar(delay_t *delay_t, uint32_t espera_ms);  // Inicia el delay
 bool DelayGPIO_NoBloqueante(delay_t *delay_t);                 // Verifica si el delay ha terminado
#endif /* API_INC_API_DELAY_H_ */
