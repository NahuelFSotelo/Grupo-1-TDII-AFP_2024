/*
 * API_delay.c
 *
 *  Created on: Jan 10, 2025
 *      Author: Nahue
 */
/* Includes ******************************************************************************/
#include "main.h"
#include "API_GPIO.h"
#include "API_delay.h"
#include <stdbool.h>
/*Defines ********************************************************************************/

/*Declaration of variables ***************************************************************/
delay_t miDelay;               // Estructura para el delay no bloqueante

/*** function of variables ***************************************************************/

// Inicializa el delay no bloqueante
void DelayGPIO_Iniciar(delay_t *delay_t, uint32_t espera_ms) {
	delay_t->startTime = HAL_GetTick(); // Obtiene el tiempo actual en milisegundos
	delay_t->espera = espera_ms;          // Establece el tiempo de espera
	delay_t->corriendo = true;        // Activa la bandera de que está corriendo
}

// Verifica si el delay ha terminado (sin bloquear el flujo)
bool DelayGPIO_NoBloqueante(delay_t *delay_t) {
	if (delay_t->corriendo) {
		// Verifica si el tiempo transcurrido es mayor o igual al tiempo de espera
		if ((HAL_GetTick() - delay_t->startTime) >= delay_t->espera) {
			delay_t->corriendo = false;  // Desactiva la bandera
			return true;  // El delay ha terminado
		}
	}
	return false;  // El delay sigue en curso
}



