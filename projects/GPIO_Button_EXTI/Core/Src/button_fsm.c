/*
 * Button FSM module
 *
 * Implementation of an event-driven finite state machine
 * for EXTI-based button handling on STM32.
 *
 * Responsibilities:
 *  - debounce handling
 *  - short press detection
 *  - long press detection
 *
 * Design principles:
 *  - no blocking delays
 *  - no application logic in ISR
 *  - main-loop-driven state machine
 *
 * Platform: STM32 + HAL
 */



#include "button_fsm.h"

/* internal time base, incremented from TIM ISR */

static volatile uint32_t btn_time_ms = 0;

/* public API */

void Button_Init(ButtonCtx_t *btn, ButtonReadFn read)
{
    btn->state = BTN_STATE_IDLE;
    btn->debounce_start_ms = 0;
    btn->press_start_ms = 0;
    btn->event = BTN_EVENT_NONE;
    btn->read = read;
}

void Button_OnExti(ButtonCtx_t *btn)
{
    /* EXTI only signals activity */
    if (btn->state == BTN_STATE_IDLE) {
        btn->state = BTN_STATE_DEBOUNCE;
        btn->debounce_start_ms = btn_time_ms;
    }
}

void Button_OnTick(ButtonCtx_t *btn)
{
    (void)btn;
    btn_time_ms++; /* global button time base (shared by all button instances) */
}

void Button_Process(ButtonCtx_t *btn)
{
    switch (btn->state)
    {
        case BTN_STATE_IDLE:
            break;

        case BTN_STATE_DEBOUNCE:
            if ((btn_time_ms - btn->debounce_start_ms) >= BTN_DEBOUNCE_MS) {
                if (btn->read()) {
                    btn->state = BTN_STATE_PRESSED;
                    btn->press_start_ms = btn_time_ms;
                } else {
                    btn->state = BTN_STATE_IDLE;
                }
            }
            break;

        case BTN_STATE_PRESSED:
            if (btn->read()) {
                if ((btn_time_ms - btn->press_start_ms) >= BTN_LONG_PRESS_MS) {
                    btn->event = BTN_EVENT_LONG;
                    btn->state = BTN_STATE_LONG;
                }
            } else {
                btn->event = BTN_EVENT_SHORT;
                btn->state = BTN_STATE_IDLE;
            }
            break;

        case BTN_STATE_LONG:
            if (!btn->read()) {
                btn->state = BTN_STATE_IDLE;
            }
            break;
    }
}
ButtonEvent_t Button_GetEvent(ButtonCtx_t *btn)
{
    ButtonEvent_t evt = btn->event;
    btn->event = BTN_EVENT_NONE;
    return evt;
}


