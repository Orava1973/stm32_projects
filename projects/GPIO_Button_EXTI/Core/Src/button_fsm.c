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
#include "main.h"

/* debounce timing (ms) */
#define BTN_DEBOUNCE_MS  30
#define BTN_LONG_PRESS_MS 2000

/* internal time base, incremented from TIM ISR */
static volatile uint32_t btn_time_ms = 0;

/* helper: read physical button */
static uint8_t Button_IsPressed(void)
{
    /* USER_BUTTON is active LOW */
    return (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin) == GPIO_PIN_RESET);
}

/* public API */

void Button_Init(ButtonCtx_t *btn)
{
    btn->state = BTN_STATE_IDLE;
    btn->debounce_start_ms = 0;
    btn->press_start_ms = 0;
    btn->short_press = 0;
    btn->long_press = 0;
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
    btn_time_ms++;
}

void Button_Process(ButtonCtx_t *btn)
{
    switch (btn->state) {

    case BTN_STATE_IDLE:
        break;

    case BTN_STATE_DEBOUNCE:
        if ((btn_time_ms - btn->debounce_start_ms) >= BTN_DEBOUNCE_MS) {
            if (Button_IsPressed()) {
                btn->state = BTN_STATE_PRESSED;
                btn->press_start_ms = btn_time_ms;   // START long press timing
            } else {
                btn->state = BTN_STATE_IDLE;
            }
        }
        break;

    case BTN_STATE_PRESSED:
    	if (Button_IsPressed()) {
        /* long press detected */
        if ((btn_time_ms - btn->press_start_ms) >= BTN_LONG_PRESS_MS) {
            btn->long_press = 1;
            btn->state = BTN_STATE_LONG;}
        }
        /* released early → short press */
        else /*if (!Button_IsPressed())*/ {
            btn->short_press = 1;
            btn->state = BTN_STATE_IDLE;
        }
        break;

    case BTN_STATE_LONG:
        /* wait for release */
        if (!Button_IsPressed()) {
            btn->state = BTN_STATE_IDLE;
        }
        break;

    /*default:
        btn->state = BTN_STATE_IDLE;
        break;*/
    }
}

uint8_t Button_WasShortPressed(ButtonCtx_t *btn)
{
    if (btn->short_press) {
        btn->short_press = 0;
        return 1;
    }
    return 0;
}

uint8_t Button_WasLongPressed(ButtonCtx_t *btn)
{
	if (btn->long_press) {
	        btn->long_press = 0;
	        return 1;
	    }
    return 0;
}
