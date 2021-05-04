#include "gate.h"

using namespace gate;

void Gate::Init(float sample_rate, dsy_gpio *pin) {
  pin_ = pin;

  sample_rate_ = sample_rate;
  inc_ = 1.0f / sample_rate_;
  gate_length_ = 0.5f;

  state_ = GATE_OFF;
  trigger_ = 0;
  ellapsed_ = 0.0f;
}

bool Gate::Process() {
  bool out = true;

  if (trigger_) {
    trigger_ = 0;

    // do not retrigger!
    if (state_ == GATE_OFF) {
      state_ = GATE_ON;
      ellapsed_ = 0.0f;
    }
  }

  if (state_ == GATE_OFF) {
    out = false;
  } else {
    ellapsed_ += inc_;
    if (ellapsed_ > gate_length_) {
      state_ = GATE_OFF;
    }
  }

  dsy_gpio_write(pin_, out);
  return out;
}