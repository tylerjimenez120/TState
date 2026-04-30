#pragma once

#include "IState.h"
#include <iostream>

// Forward declarations of static instances
class ScanningState;
class MitigationState;

class ScanningState final : public IState {
public:
  void on_enter() override {
    std::cout << "[SOC] ENTER: Activating network scan and watchdog.\n";
  }

  void on_exit() override {
    std::cout << "[SOC] EXIT: Stopping scan processes.\n";
  }

  IState *handle_event(Event event) override;

  static ScanningState *instance() {
    static ScanningState _instance;
    return &_instance;
  }
};

class MitigationState final : public IState {
public:
  void on_enter() override {
    std::cout << "[SOC] ENTER: Starting mitigation protocol (IP Block).\n";
  }

  void on_exit() override {
    std::cout << "[SOC] EXIT: Mitigation table cleanup finished.\n";
  }

  IState *handle_event(Event event) override;

  static MitigationState *instance() {
    static MitigationState _instance;
    return &_instance;
  }
};

// --- Implementation of logic with state returns ---

inline IState *ScanningState::handle_event(Event event) {
  if (event == Event::ANOMALY_DETECTED) {
    return MitigationState::instance(); // Request transition
  }
  return nullptr; // No transition
}

inline IState *MitigationState::handle_event(Event event) {
  if (event == Event::MITIGATION_DONE) {
    return ScanningState::instance(); // Request transition
  }
  return nullptr; // No transition
}