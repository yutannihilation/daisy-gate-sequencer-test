#pragma once
#ifndef GATE_H
#define GATE_H
#include "daisy_seed.h"
#include <stdint.h>
#ifdef __cplusplus

namespace gate {

enum GateState {
  GATE_OFF,
  GATE_ON,
};

class Gate {
public:
  Gate() {}
  ~Gate() {}

  void Init(float sample_rate, dsy_gpio *pin);

  bool Process();

  // Starts the gate
  inline void Trigger() { trigger_ = 1; }

  // Sets the length of the gate in seconds
  inline void SetLength(float length) { gate_length_ = length; }

private:
  dsy_gpio *pin_;     // Output pin
  float sample_rate_; // samping rate
  float inc_;         // length of one loop
  float gate_length_; // gate length in seconds
  float ellapsed_;    // elapsed time since the gate became high in seconds
  uint8_t trigger_;   // if triggered, 1
  uint8_t state_;     // whether the gate is on or offf
};

} // namespace gate

#endif
#endif
