#include "daisysp.h"
#include "daisy_seed.h"

#define PIN_GATE_OUT1 13
#define PIN_GATE_OUT2 14

#define PIN_BITCRUSH_CONTROL 15

using namespace daisysp;
using namespace daisy;

static DaisySeed seed;

static SampleRateReducer bitcrush;

dsy_gpio gate_output1, gate_output2;

static void AudioCallback(float *in, float *out, size_t size)
{
	float sig, ctrl;

	ctrl = seed.adc.GetFloat(0);

	if (ctrl > 0.5)
	{
		dsy_gpio_write(&gate_output1, true); // set high
	}
	else
	{
		dsy_gpio_write(&gate_output1, false); // set low
	}

	for (size_t i = 0; i < size; i += 2)
	{
		sig = in[i];

		bitcrush.SetFreq(powf(ctrl, 3.0) + 0.001);
		sig = bitcrush.Process(sig);

		// left out
		out[i] = sig;

		// right out
		out[i + 1] = sig;
	}
}

void setup_gate_output(const int pin, dsy_gpio *gpio)
{
	gpio->pin = seed.GetPin(pin);
	gpio->mode = DSY_GPIO_MODE_OUTPUT_PP;
	gpio->pull = DSY_GPIO_NOPULL;
	dsy_gpio_init(gpio);
	dsy_gpio_write(gpio, false); // set low
}

int main(void)
{
	// initialize seed hardware and oscillator daisysp module
	seed.Configure();
	seed.Init();
	bitcrush.Init();

	// Use pin 16 to read the voltage of the knob
	AdcChannelConfig adcConfig;
	adcConfig.InitSingle(seed.GetPin(PIN_BITCRUSH_CONTROL));
	seed.adc.Init(&adcConfig, 1);

	setup_gate_output(PIN_GATE_OUT1, &gate_output1);
	setup_gate_output(PIN_GATE_OUT2, &gate_output2);

	// start callback
	seed.adc.Start();
	seed.StartAudio(AudioCallback);

	while (1)
	{
	}
}
