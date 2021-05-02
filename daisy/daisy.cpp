#include "daisysp.h"
#include "daisy_seed.h"

using namespace daisysp;
using namespace daisy;

static DaisySeed seed;
static Oscillator lfo;
static SampleRateReducer bitcrush;

uint8_t depth;
static void AudioCallback(float *in, float *out, size_t size)
{
	float sig;
	for (size_t i = 0; i < size; i += 2)
	{
		sig = in[i];

		bitcrush.SetFreq(powf(seed.adc.GetFloat(0), 3.0) + 0.001);
		sig = bitcrush.Process(sig);

		// left out
		out[i] = sig;

		// right out
		out[i + 1] = sig;
	}
}

int main(void)
{
	// initialize seed hardware and oscillator daisysp module
	float sample_rate;
	depth = 1;
	seed.Configure();
	seed.Init();
	sample_rate = seed.AudioSampleRate();
	bitcrush.Init();

	// Use pin 16 to read the voltage of the knob
	AdcChannelConfig adcConfig;
	adcConfig.InitSingle(seed.GetPin(15));
	seed.adc.Init(&adcConfig, 1);

	// start callback
	seed.adc.Start();
	seed.StartAudio(AudioCallback);

	while (1)
	{
	}
}
