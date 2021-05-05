#include "pattern.h"

using namespace gasstove;

void Pattern::Init(float sample_rate, Metro *clock, Gate *gate1, Gate *gate2) {
  sample_rate_ = sample_rate;
  clock_ = clock;
  gate1_ = gate1;
  gate2_ = gate2;
}

void Pattern::Process() {
  if (clock_->Process()) {
    gate1_->Trigger(0.5f, 0.0f);
    gate2_->Trigger(0.5f, 0.2f);
  }

  gate1_->Process();
  gate2_->Process();
}

void Pattern::Reset() {
  clock_->Reset();
  gate1_->Reset();
  gate2_->Reset();
}
