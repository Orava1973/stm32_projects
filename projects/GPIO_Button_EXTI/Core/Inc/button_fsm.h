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

/* ===== Button states ===== */
typedef enum {
    BTN_STATE_IDLE = 0,
    BTN_STATE_DEBOUNCE,
    BTN_STATE_PRESSED,
    BTN_STATE_LONG
} ButtonState_t;

/* ===== Button events ===== */
typedef enum {
	BTN_EVENT_NONE = 0,
    BTN_EVENT_SHORT,
    BTN_EVENT_LONG
} ButtonEvent_t;

/* ===== Button context ===== */
typedef struct {
    ButtonState_t state;
    uint32_t debounce_start_ms;
    uint32_t press_start_ms;
    ButtonEvent_t event;
} ButtonCtx_t;

/* Public API */
void Button_Init(ButtonCtx_t *btn);
void Button_OnExti(ButtonCtx_t *btn);
void Button_OnTick(ButtonCtx_t *btn);
void Button_Process(ButtonCtx_t *btn);

ButtonEvent_t Button_GetEvent(ButtonCtx_t *btn);

/* timing thresholds (ms) */
#define BTN_LONG_PRESS_MS  2000
#define BTN_DEBOUNCE_MS    30

#endif /* BUTTON_FSM_H_ */
