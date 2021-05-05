#pragma once
#ifndef GASSTOVE_PATTERN_H
#define GASSTOVE_PATTERN_H
#include "daisy_seed.h"
#include "daisysp.h"
#include "gate.h"
#include <stdint.h>
#ifdef __cplusplus

using namespace daisy;
using namespace daisysp;

namespace gasstove {

class Pattern {

private:
  Metro *clock_;      // master clock
  Gate *gate1_;       // gate1
  Gate *gate2_;       // gate2
  float sample_rate_; // sample rate
  uint8_t step_;      // current step

public:
  Pattern(){};
  ~Pattern(){};

  void Init(float sample_rate, Metro *clock, Gate *gate1, Gate *gate2);

  void Process();

  void Reset();
};

} // namespace gasstove

#endif
#endif