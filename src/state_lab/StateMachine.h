#pragma once
#include "IState.h"

/**
 * @brief StateMachine (Contexto)
 * Se encarga de la gestión de transiciones y despacho de eventos.
 * Ubicación: src/state_lab/StateMachine.h
 */
class StateMachine final {
private:
  IState *_current_state{nullptr};

public:
  explicit StateMachine(IState *initial_state) : _current_state(initial_state) {
    if (_current_state) {
      _current_state->on_enter();
    }
  }

  ~StateMachine() = default;

  // Rule of 5: No permitimos copias para evitar estados inconsistentes
  StateMachine(const StateMachine &) = delete;
  StateMachine &operator=(const StateMachine &) = delete;

  // Permitimos movimiento si es necesario
  StateMachine(StateMachine &&) = default;
  StateMachine &operator=(StateMachine &&) = default;

  void dispatch(Event event) {
    if (_current_state) {
      // The state decides WHERE to go, but the machine executes the move
      IState *next_state = _current_state->handle_event(event);
      if (next_state && next_state != _current_state) {
        transition_to(next_state);
      }
    }
  }

  void transition_to(IState *next_state) {
    if (_current_state)
      _current_state->on_exit();
    _current_state = next_state;
    if (_current_state)
      _current_state->on_enter();
  }
};