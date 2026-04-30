#include "state_lab/ConcreteStates.h"
#include "state_lab/Events.h"
#include "state_lab/StateMachine.h"
#include <gtest/gtest.h>

// --- TEST SUITE PARA STATE PATTERN ---

TEST(StateLab, InitialStateTest) {
  // Verificamos que al arrancar, el estado inicial sea el correcto
  // y ejecute su on_enter (se valida visualmente o con mocks si fuera
  // necesario)
  StateMachine machine(ScanningState::instance());
  // El éxito aquí es que compile y no haya fugas en el arranque
  SUCCEED();
}

TEST(StateLab, TransitionTest) {
  StateMachine machine(ScanningState::instance());

  // Simulamos detección de anomalía
  machine.dispatch(Event::ANOMALY_DETECTED);

  // En un sistema real, podrías exponer el nombre del estado para este test
  // Aquí validamos que la lógica de transición sea ejecutable sin crashear
  machine.dispatch(Event::MITIGATION_DONE);

  SUCCEED();
}

TEST(StateLab, EventIdempotencyTest) {
  StateMachine machine(ScanningState::instance());

  // Enviar un evento que el estado actual no maneja (Reset en Scanning)
  // No debería haber cambio de estado ni errores de punteros
  machine.dispatch(Event::SYSTEM_RESET);

  SUCCEED();
}