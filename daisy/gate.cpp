#include "gate.h"

using namespace gate;

void Gate::Init(float sample_rate) {
  sample_rate_ = sample_rate;
  inc_ = 1.0f / sample_rate_;
  gate_length_ = 0.5f;

  state_ = GATE_OFF;
  trigger_ = 0;
  ellapsed_ = 0.0f;
}

bool Gate::Process() {
  if (trigger_) {
    trigger_ = 0;

    // do not retrigger!
    if (state_ == GATE_OFF) {
      state_ = GATE_ON;
      ellapsed_ = 0.0f;
    }
  }

  if (state_ == GATE_OFF) {
    return false;
  }

  ellapsed_ += inc_;
  if (ellapsed_ > gate_length_) {
    state_ = GATE_OFF;
  }

  return true;
}