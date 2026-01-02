# STM32 Projects (Embedded Portfolio)

This repository contains a collection of **STM32 embedded projects** developed using **STM32CubeIDE** and **STM32 HAL drivers**.

The primary goal of this repository is to serve as a **clean, reusable base template** and a growing **public portfolio** for **Embedded / Firmware Developer roles**.

The projects demonstrate:
- clean embedded architecture
- event-driven design
- interrupt-safe patterns
- scalable project structure
- professional Git workflow

---

## 🔧 Target Platform

- **MCU:** STM32 (tested on NUCLEO-F103RB)
- **IDE:** STM32CubeIDE
- **Framework:** STM32 HAL
- **Language:** C (C++ planned)
- **OS:** Bare-metal (FreeRTOS planned)

---

## 📁 Repository Structure

STM32_Projects/
├── README.md # Repository overview (this file)
│
├── templates/ # Stable reference templates
│ └── TIM_based_LED_blink/
│
├── projects/ # Independent STM32 projects
│ └── GPIO_Button_EXTI/
│ └── README.md # Project-specific description
│
└── workspace/ # Local STM32CubeIDE workspace (gitignored)


Each folder under `templates/` and `projects/` is a **standalone STM32CubeIDE project** that can be opened and built independently.

---

## 🧱 Templates (Base Architectures)

### TIM_based_LED_blink

A **base embedded template** demonstrating best practices:

- TIM2 used as **system tick (2 ms)**
- Interrupt-driven timing
- **No `HAL_Delay()`** in application logic
- ISR contains **only counters and event flags**
- Main loop handles **all hardware actions**
- Clear separation between:
  - timekeeping
  - event generation
  - application logic

This template is used as the **architectural foundation** for all projects in `projects/`.

---

## 🧪 Projects

### GPIO_Button_EXTI

Button handling using **EXTI interrupts** with a clean event-driven architecture:

- External interrupt (EXTI) on USER button
- Software debounce
- ISR-safe event signaling
- Main-loop-driven logic
- Preparation for **FSM-based button handling**

This project demonstrates how to evolve from a minimal template
to real input-handling logic.

See `projects/GPIO_Button_EXTI/README.md` for details.

---

## 🛡 Git & Branch Policy

- `main` branch is **stable**
- Development is done in **feature branches**
- Typical workflow:

feature/* → commit → push → merge to main


This guarantees:
- clean history
- reproducible builds
- safe experimentation

---

## 🚀 Roadmap

Planned future additions:

- Button FSM (short / long press)
- UART (interrupt & DMA)
- SPI / I2C drivers
- Event framework
- FreeRTOS-based projects
- Power management & low-power modes
- C++ abstraction layers
- CI / build checks (GitHub Actions)

---

## 👤 Author

**Vadim (Orava1973)**  
Embedded / Systems Engineer (in progress)

This repository is actively maintained and expanded as part of professional growth in embedded systems development.
