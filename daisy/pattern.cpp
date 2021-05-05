#include "pattern.h"
#include "clock.h"

// clang-format off
#define MASK_GATE1_ON    (uint8_t)(1 << 0) // 0000 0001
#define MASK_GATE1_DELAY (uint8_t)(1 << 1) // 0000 0010
#define MASK_GATE2_ON    (uint8_t)(1 << 4) // 0001 0000
#define MASK_GATE2_DELAY (uint8_t)(1 << 5) // 0010 0000

#define LENGTH_ONESHOT   0.124f
// clang-format on

using namespace gasstove;

struct SubStep {
  float length; // gate length
  float delay;  // delay before the gate starts
  float sleep;  // delay before the next substep
};

// clang-format off
const SubStep substep_pattern1[] = {
  SubStep{1.0f, 0.0f, 0.0f},
  SubStep{1.0f, 0.0f, 1.0f},
  SubStep{0.3f, 0.0f, 0.1f},
  SubStep{1.0f, 0.0f, 1.0f},
};
// clang-format on

void Pattern::Init(float sample_rate, Clock *clock, Gate *gate1, Gate *gate2) {
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
    cur_substep_ = 0;

    if (true) {
      gates_[cur_gate_]->Trigger(LENGTH_ONESHOT, 0.0f);
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
  cur_substep_ = 0;
}
