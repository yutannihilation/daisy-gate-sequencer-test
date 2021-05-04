#include "daisy_seed.h"
#include "daisysp.h"

#define PIN_GATE_OUT1 13
#define PIN_GATE_OUT2 14

// clang-format off
#define PIN_CONTROLS_BASE       15
#define OFFSET_BITCRUSH_CONTROL  0
#define OFFSET_REVERB_CONTROL1   1
#define OFFSET_REVERB_CONTROL2   2
#define OFFSET_REVERB_CONTROL3   3
#define OFFSET_REVERB_CONTROL4   4
// clang-format on

const size_t num_controls = 5;
uint8_t controls[num_controls] = {
    OFFSET_BITCRUSH_CONTROL, // bitcrush
    OFFSET_REVERB_CONTROL1,  // reverb
    OFFSET_REVERB_CONTROL2,  //
    OFFSET_REVERB_CONTROL3,  //
    OFFSET_REVERB_CONTROL4,  //
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

static Metro clock;
bool gate1_state = true;
dsy_gpio gate_output1, gate_output2;

uint32_t gate_end = 0;

static void AudioCallback(float *in, float *out, size_t size) {
  float sig, sig_tmp, dry_rate, send_rate, wet1, wet2;

  for (size_t i = 0; i < size; i += 2) {
    sig = in[i];

    // Metro needs to be processed in this for loop, otherwise it's not
    // triggered.
    if (clock.Process()) {
      dsy_gpio_write(&gate_output1, gate1_state);
      gate1_state = !gate1_state;
    }

    dry_rate = verb_mix.Process();
    send_rate = verb_send.Process();
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

  AdcChannelConfig adcConfig[num_controls];
  for (uint8_t i = 0; i < num_controls; i++) {
    setup_adcConfig(adcConfig, controls[i]);
  }
  seed.adc.Init(adcConfig, num_controls);

  // setup bitcrush
  bitcrush.Init();
  bitcrush_control.Init(seed.adc.GetPtr(OFFSET_BITCRUSH_CONTROL), sample_rate);
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

  clock.Init(1.0f, sample_rate);

  setup_gate_output(PIN_GATE_OUT1, &gate_output1);
  setup_gate_output(PIN_GATE_OUT2, &gate_output2);

  // start callback
  seed.adc.Start();
  seed.StartAudio(AudioCallback);

  while (1) {
  }
}
