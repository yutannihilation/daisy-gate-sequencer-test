#include "daisy_seed.h"
#include "daisysp.h"

#include "clock.h"
#include "gate.h"
#include "pattern.h"

#define PIN_GATE_OUT1 13
#define PIN_GATE_OUT2 14

// clang-format off
#define PIN_CONTROLS_BASE       15
#define OFFSET_BPM_CONTROL       0
#define OFFSET_ONESHOT_CONTROL   1
#define OFFSET_REVERB_CONTROL1   2
#define OFFSET_REVERB_CONTROL2   3
#define OFFSET_REVERB_CONTROL3   4
#define OFFSET_REVERB_CONTROL4   5

// ボタンは、オンになるとグランド。DaisyExamples/seed/Button の例と同じ。
// 21 pin は壊れてしまった...
#define PIN_BEAT_ON_BUTTON    22
#define PIN_REVERB_ON_BUTTON  23
// clang-format on

const size_t num_controls = 6;
uint8_t controls[num_controls] = {
    OFFSET_BPM_CONTROL,     // bpm
    OFFSET_ONESHOT_CONTROL, // oneshot length
    OFFSET_REVERB_CONTROL1, // reverb
    OFFSET_REVERB_CONTROL2, //
    OFFSET_REVERB_CONTROL3, //
    OFFSET_REVERB_CONTROL4, //
};

using namespace daisysp;
using namespace daisy;

static DaisySeed seed;

static SampleRateReducer bitcrush;
AnalogControl bitcrush_control;
Parameter bitcrush_rate;

static ReverbSc verb;
AnalogControl verb_control1, verb_control2, verb_control3, verb_control4;
Parameter verb_feedback, verb_lp_freq, verb_mix, verb_send;

Switch button1, button2;

static gasstove::Pattern pattern;
static gasstove::Clock clock;
static gasstove::Gate gate1, gate2;
dsy_gpio gate_output1, gate_output2;

AnalogControl oneshot_control, bpm_control;
Parameter oneshot, bpm;

static void AudioCallback(float *in, float *out, size_t size) {
  float sig, sig_tmp, dry_rate, send_rate, wet1, wet2;

  button1.Debounce();
  button2.Debounce();

  for (size_t i = 0; i < size; i += 2) {
    sig = in[i];

    pattern.Process(!button1.Pressed());
    // pattern.Process(false);

    dry_rate = verb_mix.Process();

    if (button2.Pressed()) {
      send_rate = verb_send.Process();
    } else {
      send_rate = 0.0f;
    }

    bitcrush.SetFreq(bitcrush_rate.Process());

    sig = bitcrush.Process(sig);
    sig_tmp = sig * send_rate;

    verb.SetFeedback(verb_feedback.Process());
    verb.SetLpFreq(verb_lp_freq.Process());
    verb.Process(sig_tmp, sig_tmp, &wet1, &wet2);

    out[i] = sig * dry_rate + wet1;
    out[i + 1] = sig * dry_rate + wet2;
  }
}

void setup_gate_output(const int pin, dsy_gpio *gpio) {
  gpio->pin = seed.GetPin(pin);
  gpio->mode = DSY_GPIO_MODE_OUTPUT_PP;
  gpio->pull = DSY_GPIO_NOPULL;
  dsy_gpio_init(gpio);
  dsy_gpio_write(gpio, false); // set low
}

void setup_adcConfig(AdcChannelConfig *adcConfig, const int offset) {
  adcConfig[offset].InitSingle(seed.GetPin(PIN_CONTROLS_BASE + offset));
};

int main(void) {
  float sample_rate;
  seed.Configure();
  seed.Init();
  sample_rate = seed.AudioSampleRate();

  // ADC
  AdcChannelConfig adcConfig[num_controls];
  for (uint8_t i = 0; i < num_controls; i++) {
    setup_adcConfig(adcConfig, controls[i]);
  }
  seed.adc.Init(adcConfig, num_controls);

  // setup bitcrush
  bitcrush.Init();
  bitcrush_control.Init(seed.adc.GetPtr(OFFSET_BPM_CONTROL), sample_rate);
  bitcrush_rate.Init(bitcrush_control, 0.001, 1.0, Parameter::EXPONENTIAL);

  // setup reverb
  verb.Init(sample_rate);

  verb_control1.Init(seed.adc.GetPtr(OFFSET_REVERB_CONTROL1), sample_rate);
  verb_feedback.Init(verb_control1, 0.f, 0.99f, Parameter::LINEAR);

  verb_control2.Init(seed.adc.GetPtr(OFFSET_REVERB_CONTROL2), sample_rate);
  verb_lp_freq.Init(verb_control2, 0.f, 20000.0f, Parameter::EXPONENTIAL);

  verb_control3.Init(seed.adc.GetPtr(OFFSET_REVERB_CONTROL3), sample_rate);
  verb_mix.Init(verb_control3, 0.f, 1.0f, Parameter::LINEAR);

  verb_control4.Init(seed.adc.GetPtr(OFFSET_REVERB_CONTROL4), sample_rate);
  verb_send.Init(verb_control4, 0.f, 1.0f, Parameter::LINEAR);

  button1.Init(seed.GetPin(PIN_BEAT_ON_BUTTON), 1000);
  button2.Init(seed.GetPin(PIN_REVERB_ON_BUTTON), 1000);

  oneshot_control.Init(seed.adc.GetPtr(OFFSET_ONESHOT_CONTROL), sample_rate);
  oneshot.Init(oneshot_control, 0.05f, 0.4f, Parameter::LINEAR);

  bpm_control.Init(seed.adc.GetPtr(OFFSET_BPM_CONTROL), sample_rate);
  bpm.Init(bpm_control, 10.0f, 180.0f, Parameter::LINEAR);

  clock.Init(120.0f, sample_rate);

  setup_gate_output(PIN_GATE_OUT1, &gate_output1);
  gate1.Init(sample_rate, &gate_output1);
  setup_gate_output(PIN_GATE_OUT2, &gate_output2);
  gate2.Init(sample_rate, &gate_output2);

  pattern.Init(sample_rate, &clock, &gate1, &gate2);

  // start callback
  seed.adc.Start();

  seed.StartAudio(AudioCallback);

  while (1) {
    clock.SetBpm(bpm.Process());
    pattern.SetOneshotLength(oneshot.Process());
  }
}
