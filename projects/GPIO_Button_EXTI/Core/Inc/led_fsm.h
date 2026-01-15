/*
 * LED FSM public interface
 *
 * Defines the public API and data structures for an
 * event-driven finite state machine used for LED control.
 *
 * This module is designed to:
 *  - control LED operating modes (OFF / ON / BLINK)
 *  - decouple LED behavior from application logic
 *  - provide a clear and minimal control interface
 *
 * The LED FSM is driven by:
 *  - explicit mode changes from application code
 *  - periodic tick events for time-based behavior (blinking)
 *
 * Design principles:
 *  - no direct GPIO access from application code
 *  - no blocking delays
 *  - ISR-safe (no logic executed inside interrupts)
 *
 * Platform: STM32 + HAL
 */

#ifndef INC_LED_FSM_H_
#define INC_LED_FSM_H_

#include <stdint.h>

typedef enum {
    LED_MODE_OFF = 0,
    LED_MODE_ON,
    LED_MODE_BLINK
} LedMode_t;

void Led_Init(void);
void Led_SetMode(LedMode_t mode);
void Led_OnTick(void);
void Led_Process(void);

#endif /* INC_LED_FSM_H_ */
