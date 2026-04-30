#include "state_lab/ConcreteStates.h"
#include "state_lab/Events.h"
#include "state_lab/StateMachine.h"
#include <iostream>
#include <vector>

/**
 * @brief Laboratorio de Patrón State (FSM) con Eventos.
 * Estructura final optimizada para sistemas embebidos.
 */
int main() {
  std::cout << "--- INICIANDO LAB: STATE MACHINE (SOC SIMULATION) ---\n"
            << std::endl;

  // 1. Instanciación del Contexto (StateMachine)
  // Se inicia con el puntero a la instancia estática de ScanningState.
  // Esto ejecuta automáticamente ScanningState::on_enter().
  StateMachine soc_machine(ScanningState::instance());

  // 2. Definición de la cola de eventos
  // Simulamos estímulos externos (ej. interrupciones de red o sensores).
  const std::vector<Event> event_queue = {
      Event::SCAN_COMPLETED,   // No causa transición (permanece en SCAN)
      Event::ANOMALY_DETECTED, // Dispara transición a MITIGATION
      Event::MITIGATION_DONE,  // Dispara transición de regreso a SCAN
      Event::SYSTEM_RESET      // Ejemplo de evento no manejado/futuro
  };

  // 3. Bucle de ejecución de la máquina
  // Despachamos los eventos de forma secuencial.
  for (const auto &event : event_queue) {
    std::cout << "\n[MAIN] Despachando Evento ID: " << static_cast<int>(event)
              << std::endl;
    soc_machine.dispatch(event);
  }

  std::cout << "\n--- LABORATORIO FINALIZADO CON ÉXITO ---" << std::endl;

  return 0;
}