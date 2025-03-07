/*
 * API_debounce.h
 *
 *  Created on: Nov 29, 2024
 *      Author: Nahue
 */
#include <stdbool.h>
#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_
//////////variables/////////////////
typedef enum {
    BUTTON_UP,       // El botón está en su estado normal sin presionar (alto o bajo según configuración).
    BUTTON_FALLING,  // Se detectó un posible cambio al presionar el botón, pero está en evaluación para evitar falsos positivos.
    BUTTON_DOWN,     // El botón está confirmado como presionado después del tiempo de debounce.
    BUTTON_RISING    // Se detectó un posible cambio al soltar el botón, pero está en evaluación para evitar falsos positivos.
} debounceState_t;



/////////////////declaracion de funciones ////////////////////////////
// Inicializa la máquina de estados de debounce, configurando el estado inicial.
// Debe llamarse antes de usar la máquina de estados.
void debounceFSM_init();

// Actualiza el estado de la máquina de estados de debounce.
// Se debe llamar periódicamente (por ejemplo, en el loop principal o en un temporizador).
// Detecta cambios de estado del botón y maneja el debounce.
void debounceFSM_update();

// Función que se llama cuando se detecta que el botón ha sido presionado.
// Aquí puedes realizar una acción específica, como registrar el evento o encender un LED.
void buttonPressed(void);

// Función que se llama cuando se detecta que el botón ha sido liberado.
// En este caso, debe invertir el estado del LED3 (encender si está apagado, o apagar si está encendido).
void buttonReleased(void);
/**
 * @brief Evalúa el estado de una variable booleana y la resetea si es true.
 *
 * @param keyState Puntero a la variable que representa el estado de la tecla.
 * @return true Si la variable estaba en true.
 * @return false Si la variable estaba en false.
 */
bool readKey();


#endif /* API_INC_API_DEBOUNCE_H_ */
