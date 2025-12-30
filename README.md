# STM32 Projects (Embedded Portfolio)

This repository contains a collection of **STM32 embedded projects** developed using **STM32CubeIDE** and **HAL drivers**.  
The primary goal of this repository is to serve as a **clean, reusable base template** and a growing **portfolio for Embedded Developer roles**.

---

## 🔧 Target Platform

- **MCU:** STM32 (tested on Nucleo-F103RB)
- **IDE:** STM32CubeIDE
- **Framework:** STM32 HAL
- **Language:** C (with C++ planned)
- **OS:** Bare-metal (RTOS projects planned)

---

## 📁 Repository Structure

stm32_projects/
│
├── TIM_based_LED_blink/
│ └── TIM_based_LED_blink/
│ ├── Core/
│ ├── Drivers/
│ ├── STM32CubeMX (.ioc)
│ └── README.md (project-specific description)
│
├── .gitignore
├── README.md


Each subdirectory represents an **independent STM32 project** that can be opened directly in STM32CubeIDE.

---

## 🧱 Base Template (Key Project)

### `TIM_based_LED_blink`

A **base embedded template** demonstrating best practices:

- TIM2 used as **system tick (2 ms)**
- Interrupt-driven timing (no `HAL_Delay` in main logic)
- ISR contains **only counters and event flags**
- Main loop handles **all hardware actions**
- Clear separation between:
  - timekeeping
  - event handling
  - application logic

This project is used as a **starting point for all future STM32 projects** in this repository.

---

## 🛡 Branch Policy

- `main` branch is **protected**
- Direct pushes to `main` are **not allowed**
- All changes must go through:

feature branch → Pull Request → Merge

- This guarantees a **stable and reproducible template**

---

## 🚀 Development Workflow

Typical workflow for new projects:

```bash
git checkout -b feature_new_project
# develop
git commit -m "Add new STM32 project"
git push origin feature_new_project
# Open Pull Request on GitHub

📌 Roadmap

Planned future additions:

UART (interrupt & DMA)

SPI / I2C drivers

Button handling & debouncing

FreeRTOS-based projects

Power management & low-power modes

C++ abstraction layers

Unit-testing / build checks (GitHub Actions)

👤 Author

Vadim (Orava1973)
Embedded / Systems Engineer (in progress)

This repository is actively maintained and expanded as part of professional growth in embedded systems development.