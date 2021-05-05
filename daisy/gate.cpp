#include "gate.h"

using namespace gasstove;

void Gate::Init(float sample_rate, dsy_gpio *pin) {
  pin_ = pin;

  sample_rate_ = sample_rate;
  inc_ = 1.0f / sample_rate_;
  gate_length_ = 0.5f;

  Gate::Reset();
}

void Gate::Trigger(float length, float delay) {
  trigger_ = 1;
  gate_length_ = length;
  gate_delay_ = delay;
}

bool Gate::Process() {
  bool out = false;

  if (trigger_) {
    trigger_ = 0;

    // do not retrigger!
    if (state_ == GATE_OFF) {
      state_ = GATE_ON;
      ellapsed_ = 0.0f;
    }
  }

  if (state_ == GATE_ON) {
    if (ellapsed_ > gate_delay_) {
      out = true;
    }

    ellapsed_ += inc_;
    if (ellapsed_ > gate_length_ + gate_delay_) {
      state_ = GATE_OFF;
    }
  }

  dsy_gpio_write(pin_, out);
  return out;
}

void Gate::Reset() {
  state_ = GATE_OFF;
  trigger_ = 0;
  ellapsed_ = 0.0f;

  // turn off the gate
  dsy_gpio_write(pin_, false);
}
