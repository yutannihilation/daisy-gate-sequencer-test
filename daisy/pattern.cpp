#include "pattern.h"

#define MASK_GATE1_ON (uint8_t)(1 << 0) // 0000 0001
#define MASK_GATE2_ON (uint8_t)(1 << 1) // 0000 0010

using namespace gasstove;

const uint8_t pattern1[] = {0b00000001, 0b00000011, 0b00000001, 0b00000011,
                            0b00000001, 0b00000011, 0b00000001, 0b00000011};

void Pattern::Init(float sample_rate, Metro *clock, Gate *gate1, Gate *gate2) {
  sample_rate_ = sample_rate;
  clock_ = clock;
  gate1_ = gate1;
  gate2_ = gate2;

  max_step_ = 8;

  Pattern::Reset();
}

void Pattern::Process() {
  if (clock_->Process()) {
    if (pattern1[step_] & MASK_GATE1_ON) {
      gate1_->Trigger(0.5f, 0.0f);
    }

    if (pattern1[step_] & MASK_GATE2_ON) {
      gate2_->Trigger(0.5f, 0.0f);
    }

    step_++;
  }

  gate1_->Process();
  gate2_->Process();
}

void Pattern::Reset() {
  clock_->Reset();
  gate1_->Reset();
  gate2_->Reset();

  step_ = 0;
}
