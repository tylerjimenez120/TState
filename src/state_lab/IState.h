#pragma once
#include "Events.h"

class StateMachine;

class IState {
public:
  IState() = default;
  virtual ~IState() = default;

  // Rule of 5: Bloqueo total de copia y movimiento
  // Esto garantiza que el estado sea una entidad fija en memoria
  IState(const IState &) = delete;
  IState &operator=(const IState &) = delete;
  IState(IState &&) = delete;
  IState &operator=(IState &&) = delete;

  virtual void on_enter() = 0;
  virtual IState *handle_event(Event event) = 0;
  virtual void on_exit() = 0;
};