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
  subptn_even_1beat,
  // subptn_even_2beats,

  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  // subptn_rest_4beats_2,

  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  // subptn_even_2beats,

  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_even_1beat,
  subptn_rest_8beats_6,
};
// clang-format on

void Pattern::Init(float sample_rate, Clock *clock, Gate *gate1, Gate *gate2) {
  sample_rate_ = sample_rate;
  clock_ = clock;

  gates_[0] = gate1;
  gates_[1] = gate2;

  oneshot_length_ = 0.125f;

  Pattern::Reset();
}

void Pattern::Process(bool mute) {
  if (clock_->Process()) {
    cur_step_ = (cur_step_ + 1) % max_step_;
    cur_substep_ = 0;
    // 表拍はつねに同じ方から出す。そうしないとリズムがかなりよれて聴こえることになる
    cur_gate_ = 0;
  }

  SubStep *ptn = pattern[cur_step_ % n_pattern];

  if (ptn[cur_substep_].start <= 1.0f &&
      ptn[cur_substep_].start <= clock_->GetPhase()) {
    float gate_length;
    switch (ptn[cur_substep_].length) {
    case GATE_LENGTH_ONESHOT:
      gate_length = oneshot_length_;
      break;

    default:
      gate_length = 1.0f;
      break;
    }

    if (!mute) {
      gates_[cur_gate_]->Trigger(gate_length, ptn[cur_substep_].delay);
    }

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
    gates_[i]->Reset();
  }

  cur_gate_ = 0;
  cur_step_ = 0;
  cur_substep_ = 0;
}
