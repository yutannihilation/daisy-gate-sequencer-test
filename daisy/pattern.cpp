#include "pattern.h"
#include "clock.h"

// clang-format off
#define MASK_GATE1_ON    (uint8_t)(1 << 0) // 0000 0001
#define MASK_GATE1_DELAY (uint8_t)(1 << 1) // 0000 0010
#define MASK_GATE2_ON    (uint8_t)(1 << 4) // 0001 0000
#define MASK_GATE2_DELAY (uint8_t)(1 << 5) // 0010 0000

#define LENGTH_ONESHOT 0.124f
#define LENGTH_LONG    1.0f
// clang-format on

using namespace gasstove;

struct SubStep {
  float start;  // when the gate starts **in phase**
  float length; // gate length **in seconds**
};

struct SubStepPattern {
  uint8_t n;
  SubStep substeps[4];
};

SubStepPattern substep_pattern1 = {
  n : 4,
  substeps : {
      SubStep{0.0f, LENGTH_ONESHOT},
      SubStep{0.0f, LENGTH_ONESHOT},
      SubStep{0.5f, LENGTH_ONESHOT},
      SubStep{0.75f, LENGTH_ONESHOT},
  }
};

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
    cur_step_ = (cur_step_ + 1) % max_step_;
    cur_substep_ = 0;
  }

  if (substep_pattern1.substeps[cur_substep_].start <= clock_->GetPhase() &&
      cur_substep_ < substep_pattern1.n) {
    gates_[cur_gate_]->Trigger(substep_pattern1.substeps[cur_substep_].length,
                               0.0f);
    cur_gate_ = (cur_gate_ + 1) % num_of_gates;
    cur_substep_ = (cur_substep_ + 1);
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
