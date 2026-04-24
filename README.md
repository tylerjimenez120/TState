# High-Performance State Pattern Lab (C++20)

A robust, deterministic, and memory-efficient Finite State Machine (FSM) implementation designed for embedded systems (ESP32/STM32). This project implements the **State Design Pattern** using modern C++ standards to ensure hardware safety and high performance.

## 🛠 Technical Highlights

-   **Zero Dynamic Allocation**: Uses static instances to prevent heap fragmentation, critical for long-running embedded applications.
-   **Rule of Five Compliance**: Enforces strict memory management by deleting copy and move operations in the State Interface.
-   **Header-Only Architecture**: Facilitates aggressive compiler optimizations (inlining) and simplifies integration into firmware projects.
-   **Thread-Safe Design**: Minimalist context switching, compatible with FreeRTOS tasks.
-   **C++20 Standards**: Utilizes `enum class`, `final` specifiers, and `inline` implementations for circular dependency resolution.

## 📂 Project Structure

-   `src/state_lab/Events.h`: Defines the system signal catalog (Enums).
-   `src/state_lab/IState.h`: The abstract interface for all concrete states.
-   `src/state_lab/StateMachine.h`: The "Context" class that manages state transitions.
-   `src/state_lab/ConcreteStates.h`: Logic implementation for states (e.g., Scanning, Mitigation).
-   `test/`: GoogleTest suite for validating transition logic and idempotency.

## 🚀 Getting Started

### Prerequisites
-   CMake 3.18+
-   G++ / Clang with C++20 support
-   GoogleTest (automatically fetched via CMake)

### Build Instructions
```bash
mkdir build && cd build
cmake ..
make




tyler-jmz@tyler:~/esp/codigos-tyler/examples/patrones/TState/build$ ./src/state_app 
--- INICIANDO LAB: STATE MACHINE (SOC SIMULATION) ---

[SOC] ENTER: Activando escaneo de red y watchdog.

[MAIN] Despachando Evento ID: 0

[MAIN] Despachando Evento ID: 1
[SOC] EXIT: Deteniendo procesos de escaneo.
[SOC] ENTER: Iniciando protocolo de mitigación (Bloqueo IP).

[MAIN] Despachando Evento ID: 3
[SOC] EXIT: Limpieza de tablas de mitigación finalizada.
[SOC] ENTER: Activando escaneo de red y watchdog.

[MAIN] Despachando Evento ID: 2

--- LABORATORIO FINALIZADO CON ÉXITO ---
tyler-jmz@tyler:~/esp/codigos-tyler/examples/patrones/TState/build$ 