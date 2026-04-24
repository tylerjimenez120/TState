#pragma once
#include "IState.h"
#include "StateMachine.h"
#include <iostream>

// Forward Declaration para que Scanning conozca a Mitigation
class MitigationState;

class ScanningState final : public IState {
public:
  // Implementación de ciclo de vida
  void on_enter() override {
    std::cout << "[SOC] ENTER: Activando escaneo de red y watchdog.\n";
  }

  void handle_event(StateMachine &machine, Event event) override;

  void on_exit() override {
    std::cout << "[SOC] EXIT: Deteniendo procesos de escaneo.\n";
  }

  static ScanningState *instance() {
    static ScanningState _instance;
    return &_instance;
  }
};

class MitigationState final : public IState {
public:
  void on_enter() override {
    std::cout
        << "[SOC] ENTER: Iniciando protocolo de mitigación (Bloqueo IP).\n";
  }

  void handle_event(StateMachine &machine, Event event) override {
    if (event == Event::MITIGATION_DONE) {
      machine.transition_to(ScanningState::instance());
    }
  }

  void on_exit() override {
    std::cout << "[SOC] EXIT: Limpieza de tablas de mitigación finalizada.\n";
  }

  static MitigationState *instance() {
    static MitigationState _instance;
    return &_instance;
  }
};

// Implementación de la transición para evitar dependencia circular
inline void ScanningState::handle_event(StateMachine &machine, Event event) {
  if (event == Event::ANOMALY_DETECTED) {
    machine.transition_to(MitigationState::instance());
  }
}