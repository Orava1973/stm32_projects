/*
 * Button FSM public interface
 *
 * Defines the public API and data structures for an
 * event-driven finite state machine used for button handling.
 *
 * This module is designed to:
 *  - process EXTI-based button events
 *  - handle debounce without blocking delays
 *  - detect short and long button presses
 *
 * The FSM is driven from the main loop and is ISR-safe:
 *  - interrupts only signal events
 *  - all logic is executed outside ISR context
 *
 * Platform: STM32 + HAL
 */

#ifndef BUTTON_FSM_H_
#define BUTTON_FSM_H_

#include <stdint.h>

typedef enum {
    BTN_STATE_IDLE = 0,
    BTN_STATE_DEBOUNCE,
    BTN_STATE_PRESSED,
    BTN_STATE_LONG
} ButtonState_t;

typedef struct {
    ButtonState_t state;
    uint32_t timestamp;
    uint8_t short_press;
    uint8_t long_press;
} ButtonCtx_t;

/* Public API */
void Button_Init(ButtonCtx_t *btn);
void Button_OnExti(ButtonCtx_t *btn);
void Button_OnTick(ButtonCtx_t *btn);
void Button_Process(ButtonCtx_t *btn);

uint8_t Button_WasShortPressed(ButtonCtx_t *btn);
uint8_t Button_WasLongPressed(ButtonCtx_t *btn);



#endif /* BUTTON_FSM_H_ */
