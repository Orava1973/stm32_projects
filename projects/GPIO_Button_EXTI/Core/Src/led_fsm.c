/*
 * LED FSM module
 *
 * Implementation of an event-driven finite state machine
 * for LED control on STM32.
 *
 * Responsibilities:
 *  - manage LED operating modes (OFF / ON / BLINK)
 *  - handle time-based blinking behavior
 *  - provide a single point of control for LED GPIO
 *
 * Design principles:
 *  - no blocking delays
 *  - no application logic inside ISR
 *  - ISR used only as a time base (tick source)
 *  - all state transitions are explicit
 *
 * Usage model:
 *  - Led_SetMode() is called from application logic
 *  - Led_OnTick() is called periodically from timer ISR
 *  - Led_Process() is reserved for future extensions
 *
 * Platform: STM32 + HAL
 */

#include "led_fsm.h"
#include "main.h"

/* параметры */
#define LED_BLINK_PERIOD_MS 500
#define SYS_TICK_PERIOD_MS   2
static LedMode_t led_mode = LED_MODE_OFF;
static uint32_t led_tick = 0;

void Led_Init(void)
{
    led_mode = LED_MODE_OFF;
    led_tick = 0;
    HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
}

void Led_SetMode(LedMode_t mode)
{
    led_mode = mode;
    led_tick = 0;

    if (mode == LED_MODE_ON) {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
    }
    else if (mode == LED_MODE_OFF) {
        HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
    }
}

void Led_OnTick(void)
{
    if (led_mode != LED_MODE_BLINK)
        return;

    if (++led_tick >= (LED_BLINK_PERIOD_MS / SYS_TICK_PERIOD_MS)) {
        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
        led_tick = 0;
    }
}
void Led_Process(void)
{
	 /* Reserved for future non-tick-based LED logic */
}
