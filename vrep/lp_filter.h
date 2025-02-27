#pragma once
#define PI_F 3.141592653589793


class LowPassFilter2p
{
public:
	// constructor
	LowPassFilter2p();
	//{
	//	//// set initial parameters
	//	//set_cutoff_frequency(sample_freq, cutoff_freq);
	//	//_delay_element_1 = _delay_element_2 = 0;
	//}

	// change parameters
	void set_cutoff_frequency(float sample_freq, float cutoff_freq);

	// apply - Add a new raw value to the filter 
	// and retrieve the filtered result
	float apply(float sample);

	// return the cutoff frequency
	float get_cutoff_freq(void) const 
	{
		return _cutoff_freq;
	}

private:
	float           _cutoff_freq;
	float           _a1;
	float           _a2;
	float           _b0;
	float           _b1;
	float           _b2;
	float           _delay_element_1;        // buffered sample -1
	float           _delay_element_2;        // buffered sample -2
};