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

  /**
   * @brief Despacha un evento al estado actual.
   */
  void dispatch(Event event) {
    if (_current_state) {
      _current_state->handle_event(*this, event);
    }
  }

  /**
   * @brief Cambia el puntero del estado actual y ejecuta callbacks de
   * salida/entrada.
   */
  void transition_to(IState *next_state) {
    if (_current_state) {
      _current_state->on_exit();
    }
    _current_state = next_state;
    if (_current_state) {
      _current_state->on_enter();
    }
  }
};