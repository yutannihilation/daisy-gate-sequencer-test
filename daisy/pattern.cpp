#include "pattern.h"

// clang-format off
#define MASK_GATE1_ON    (uint8_t)(1 << 0) // 0000 0001
#define MASK_GATE1_DELAY (uint8_t)(1 << 1) // 0000 0010
#define MASK_GATE2_ON    (uint8_t)(1 << 4) // 0001 0000
#define MASK_GATE2_DELAY (uint8_t)(1 << 5) // 0010 0000

#define LENGTH_ONESHOT   0.124f
// clang-format on

using namespace gasstove;

// clang-format off
const uint8_t pattern1[] = {
  0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00010001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00110001, 0b00000001, 0b00110001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00010001, 0b00000001, 0b00010001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00010001, 0b00110001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000001, 0b00000001, 0b00110001, 0b00000001, 0b00010001, 0b00000001, 0b00110001, 0b00000001,
  0b00000001, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00000001, 0b00000001, 0b00000001,
  0b00000000, 0b00000001, 0b00000001, 0b00000001, 0b00010001, 0b00110001, 0b00010001, 0b00110001,
};
// clang-format on

void Pattern::Init(float sample_rate, Metro *clock, Gate *gate1, Gate *gate2) {
  sample_rate_ = sample_rate;
  clock_ = clock;

  gates_[0] = gate1;
  gates_[1] = gate2;

  max_step_ = 2;
  delay_ = 0.1f;
  swing_ = 0.1f;

  Pattern::Reset();
}

void Pattern::Process() {
  if (clock_->Process()) {
    float delay1 = (pattern1[cur_step_] & MASK_GATE1_DELAY) ? delay_ : 0.0f;
    float swing = (cur_step_ % 2) == 1 ? swing_ : 0.0f;

    if (pattern1[cur_step_] & MASK_GATE1_ON) {
      gates_[cur_gate_]->Trigger(LENGTH_ONESHOT, delay1 + swing);
      cur_gate_ = (cur_gate_ + 1) % num_of_gates;
    }

    cur_step_ = (cur_step_ + 1) % max_step_;
  }

  for (uint8_t i = 0; i < num_of_gates; i++) {
    gates_[i]->Process();
  }
}

void Pattern::Reset() {
  clock_->Reset();

  for (uint8_t i = 0; i < num_of_gates; i++) {
    gates_[i]->Process();
  }

  cur_gate_ = 0;
  cur_step_ = 0;
}
