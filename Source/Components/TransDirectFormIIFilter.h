/*
  ==============================================================================

	TransDirectFormIIFilter.h
	Created: 28 Apr 2015 3:16:59pm
	Author:  Jordan

  ==============================================================================
*/

#ifndef TRANSDIRECTFORMIIFILTER_H_INCLUDED
#define TRANSDIRECTFORMIIFILTER_H_INCLUDED

#define _USE_MATH_DEFINES 

#include <cmath>
#include <complex>
#include "..\Utilities\DspUtilities.h"

using std::pow;
using std::tan;
using std::sqrt;
using std::abs;

// For filter response
using std::complex;
using std::polar;

//==============================================================================
enum {
	bq_type_lowpass = 0,
	bq_type_highpass, 
	bq_type_bandpass,
	bq_type_notch,
	bq_type_peak,
	bq_type_lowshelf,
	bq_type_highshelf
};

//==============================================================================
class TransDirectFormIIFilter {
public:
	// Create and initialize the filter with default values defined in constructor.
	TransDirectFormIIFilter();

	// Initialize the filter with specific (static) parameters. Useful for
	// using as a static filter; not modulating parameters.
	TransDirectFormIIFilter(int type, double Fc, double res, double peakGaindB);

	~TransDirectFormIIFilter();

	/*
	Sets the type of the filter. This filter can choose between 7 different
	types using the enums listed below or the int given to each.
	0: bq_type_lowpass
	1: bq_type_highpass
	2: bq_type_bandpass
	3: bq_type_notch
	4: bq_type_peak
	5: bq_type_lowshelf
	6: bq_type_highshelf
	*/
	void setType(int type);

	// Used for setting the resonance amount. Range: (0-1)
	void setResonance(double resonance);

	// Used for changing the filter's cutoff parameter (Hz)
	void setCutoff(double Fc);

	void setPitch(double pitch);

	/**
	*	Used for changing the peak gain (dB) of some filter types:
	*	Peak (bq_type_peak)
	*	Lowshelf (bq_type_lowshelf)
	*	Highshelf (bq_type_highshelf)
	*/
	void setPeakGain(double peakGaindB);

	// Statically set the filters parameters.
	void setFilter(int type, double Fc, double res, double peakGaindB);

	/**	
	*	Performs the actual processing for one sample of data, on 2 channels.
	*	If 2 channels are needed (stereo), use channel index (channelIdx) to 
	*	specify which channel is being processed (i.e. 0 for left, 1 for right).
	*/
	float processChannel(float input, int channelIndex);

	// Set the sample rate used by the host. Needs to be used to accurately
	// calculate the coefficients of the filter from the cutoff.
	void setSampleRate(double sampleRate);

	complex<double> getResponse(float frequency);

	double getAmplitudeResponse(double frequency) {
		return abs(getResponse(frequency));
	}

	double magnitudeResponse(float frequency);

protected:
	// Calculate the coefficients for the filter. 
	// Uses different coefficients for different filter types
	void calcFilter(void);

	int type;							// filters type (LP, HP, BP, etc.)
	double a0, a1, a2, b1, b2;			// coefficients
	double cutoff, Q, peakGain;				// parameters
	double z1_A[2], z2_A[2];			// arrays of states (z^-1) for stereo processing
	double sampleRate;
};

inline float TransDirectFormIIFilter::processChannel(float input, int channelIdx)
{
	double out = input * a0 + z1_A[channelIdx];
	z1_A[channelIdx] = (input * a1) + z2_A[channelIdx] - (b1 * out);
	z2_A[channelIdx] = (input * a2) - (b2 * out);
	return out;
}

//==============================================================================

#endif  // TRANSDIRECTFORMIIFILTER_H_INCLUDED
