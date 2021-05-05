#include "pattern.h"
#include "clock.h"
#include "substeps.h"

using namespace gasstove;

// clang-format off
const uint8_t n_pattern = 32;
SubStep *pattern[] = {
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_2beats,

  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_rest_4beats_2,

  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_2beats,

  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_rest_4beats_2,
};
// clang-format on

void Pattern::Init(float sample_rate, Clock *clock, Gate *gate1, Gate *gate2) {
  sample_rate_ = sample_rate;
  clock_ = clock;

  gates_[0] = gate1;
  gates_[1] = gate2;

  max_step_ = 32;
  delay_ = 0.1f;
  swing_ = 0.1f;

  Pattern::Reset();
}

void Pattern::Process() {
  if (clock_->Process()) {
    cur_step_ = (cur_step_ + 1) % max_step_;
    cur_substep_ = 0;
  }

  SubStep *ptn = pattern[cur_step_ % n_pattern];

  if (ptn[cur_substep_].start <= 1.0f &&
      ptn[cur_substep_].start <= clock_->GetPhase()) {
    gates_[cur_gate_]->Trigger(ptn[cur_substep_].length,
                               ptn[cur_substep_].delay);
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
