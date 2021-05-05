// Original code is from DaisySP:
// https://github.com/electro-smith/DaisySP/blob/master/Source/Utility/metro.h

#pragma once
#ifndef GASSTOVE_CLOCK_H
#define GASSTOVE_CLOCK_H
#include <stdint.h>
#ifdef __cplusplus

namespace gasstove {
/// Creates a clock signal at a specific BPM.
class Clock {
public:
  Clock() {}
  ~Clock() {}

  void Init(float bpm, float sample_rate);

  uint8_t Process();

  inline void Reset() { phs_ = 0.0f; }

  void SetBpm(float bpm);

  inline float GetBpm() { return bpm_; }

  inline float GetPhase() { return phs_; }

private:
  float bpm_;
  float phs_, sample_rate_, phs_inc_;
};
} // namespace gasstove
#endif
#endif
