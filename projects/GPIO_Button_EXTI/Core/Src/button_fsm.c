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


/* timing parameters */
#define BTN_DEBOUNCE_MS  30

static volatile uint32_t btn_time_ms = 0;
static uint8_t Button_IsPressed(void)
{
    return (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_Port, USER_BUTTON_Pin) == GPIO_PIN_SET);
}




void Button_Init(ButtonCtx_t *btn)
{
    btn->state = BTN_STATE_IDLE;
    btn->timestamp = 0;
    btn->short_press = 0;
    btn->long_press = 0;
}

void Button_OnExti(ButtonCtx_t *btn)
{
	if (btn->state == BTN_STATE_IDLE) {
	        btn->state = BTN_STATE_DEBOUNCE;
	        btn->timestamp = btn_time_ms;
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
        /* nothing to do */
        break;

    case BTN_STATE_DEBOUNCE:
        if ((btn_time_ms - btn->timestamp) >= BTN_DEBOUNCE_MS) {
            if (Button_IsPressed()) {
                btn->state = BTN_STATE_PRESSED;
            } else {
                btn->state = BTN_STATE_IDLE;
            }
        }
        break;

    case BTN_STATE_PRESSED:
        if (!Button_IsPressed()) {
            btn->short_press = 1;
            btn->state = BTN_STATE_IDLE;
        }
        break;

    default:
        btn->state = BTN_STATE_IDLE;
        break;
    }
}


uint8_t Button_WasShortPressed(ButtonCtx_t *btn)
{
    (void)btn;
    return 0;
}

uint8_t Button_WasLongPressed(ButtonCtx_t *btn)
{
    (void)btn;
    return 0;
}

