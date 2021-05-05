#pragma once
#ifndef GASSTOVE_GATE_H
#define GASSTOVE_GATE_H
#include "daisy_seed.h"
#include <stdint.h>
#ifdef __cplusplus

namespace gasstove {

enum GateState {
  GATE_OFF,
  GATE_ON,
};

class Gate {

private:
  dsy_gpio *pin_;     // Output pin
  float sample_rate_; // samping rate
  float inc_;         // length of one loop
  float gate_length_; // gate length in seconds
  float gate_delay_;  // seconds before starting gate
  float ellapsed_;    // elapsed time since the gate became high in seconds
  uint8_t trigger_;   // if triggered, 1
  uint8_t state_;     // whether the gate is on or off

public:
  Gate() {}
  ~Gate() {}

  void Init(float sample_rate, dsy_gpio *pin);

  bool Process();

  // Starts the gate
  void Trigger(float length, float delay);

  void Reset();
};

} // namespace gasstove

#endif
#endif
