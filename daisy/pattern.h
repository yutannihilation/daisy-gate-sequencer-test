#pragma once
#ifndef GASSTOVE_PATTERN_H
#define GASSTOVE_PATTERN_H
#include "clock.h"
#include "daisy_seed.h"
#include "daisysp.h"
#include "gate.h"
#include <stdint.h>
#ifdef __cplusplus

using namespace daisy;
using namespace daisysp;

namespace gasstove {

const int num_of_gates = 2;

class Pattern {

private:
  float sample_rate_; // sample rate

  Clock *clock_;              // master clock
  Gate *gates_[num_of_gates]; // gates
  uint8_t cur_gate_;          // 0 or 1

  uint8_t max_step_; // max step
  uint8_t cur_step_; // current step

  uint8_t cur_substep_; // current substep
  float phase_;         // 0-1
  float phase_inc_;     // phase increment of 1 step

  float oneshot_length_;

public:
  Pattern(){};
  ~Pattern(){};

  void Init(float sample_rate, Clock *clock, Gate *gate1, Gate *gate2);

  void Process();

  void Reset();

  inline void SetSteps(uint8_t max_step) { max_step_ = max_step; }

  inline void SetOneshotLength(float length) { oneshot_length_ = length; };
};

} // namespace gasstove

#endif
#endif