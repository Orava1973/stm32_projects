# GPIO_Button_EXTI — Event-Driven Button Handling (FSM)

This project demonstrates **robust button handling** on STM32 using
**EXTI interrupts** and a **finite state machine (FSM)**.

The focus is on **clean embedded architecture**, not on raw GPIO polling.

---

## 🎯 Key Goals

- No blocking delays (`HAL_Delay`)
- No logic inside interrupts
- Deterministic button behavior
- Scalable architecture (FSM-based)
- Clear separation of responsibilities

---

## 🔧 Platform

- MCU: STM32F103RB (NUCLEO-F103RB)
- IDE: STM32CubeIDE
- Framework: STM32 HAL
- OS: Bare-metal

---

## 🧠 Architecture Overview

### Event Flow

Button → EXTI Interrupt → Event Flag
↓
FSM in main loop
↓
Application-level actions


- **ISR** only signals events
- **Timing** handled by system tick
- **FSM** runs in the main loop

---

## 🧱 Finite State Machine (FSM)

### States

- `IDLE` — button released
- `DEBOUNCE` — signal stabilization
- `PRESSED` — stable press
- `LONG_PRESS` — long press detected

### Transitions

- EXTI interrupt triggers state evaluation
- Timing handled via non-blocking counters
- Long press detected without blocking delays

---

## ⏱ Timing Parameters

- Debounce: ~30 ms
- Long press: ~1000 ms

(All timings are configurable constants)

---

## 📁 Project Structure

GPIO_Button_EXTI/
├── Core/
│ ├── Src/
│ │ ├── main.c
│ │ └── button_fsm.c
│ └── Inc/
│ └── button_fsm.h
├── Drivers/
├── GPIO_Button_EXTI.ioc
└── README.md


---

## 🧩 Why This Matters

This project reflects **real-world embedded constraints**:

- Interrupt safety
- Predictable timing
- Maintainable logic
- Easy extension (double click, auto-repeat, etc.)

It is designed as a **production-ready pattern**, not a demo.

---

## 🚀 Next Steps

Planned extensions:

- Double-click detection
- Configurable button actions
- Integration into event framework
- Reuse in FreeRTOS environment

---

## 👤 Author

Vadim (Orava1973)  
Embedded / Systems Engineer (in progress)
