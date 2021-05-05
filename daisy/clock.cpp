// Original code is from DaisySP:
// https://github.com/electro-smith/DaisySP/blob/master/Source/Utility/metro.cpp

#include "clock.h"
#include <math.h>

using namespace gasstove;

void Clock::Init(float bpm, float sample_rate) {
  bpm_ = bpm;
  phs_ = 0.0f;
  sample_rate_ = sample_rate;
  phs_inc_ = 60.0f / (bpm_ * sample_rate_);
}

uint8_t Clock::Process() {
  phs_ += phs_inc_;
  if (phs_ >= 1.0f) {
    phs_ -= 1.0f;
    return 1;
  }
  return 0;
}

void Clock::SetBpm(float bpm) {
  bpm_ = bpm;
  phs_inc_ = 60.0f / (bpm_ * sample_rate_);
}
