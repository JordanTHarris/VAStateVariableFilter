/*
  ==============================================================================

	VAStateVariableFilter.cpp
	Created: 10 May 2015 2:41:43pm
	Author:  Jordan Harris

  ==============================================================================
*/

#include "VAStateVariableFilter.h"

VAStateVariableFilter::VAStateVariableFilter()
{
	sampleRate = 44100.0f;				// default sample rate when constructed
	filterType = SVFLowpass;			// lowpass filter by default

	gCoeff = 1.0f;
	RCoeff = 1.0f;
	KCoeff = 0.0f;

	cutoffFreq = 1000.0f;
	Q = resonanceToQ(0.5);

	z1_A[0] = z2_A[0] = 0.0f;
	z1_A[1] = z2_A[0] = 0.0f;
}

VAStateVariableFilter::~VAStateVariableFilter()
{
}

// Member functions for setting the filter's parameters (and sample rate).
//==============================================================================
void VAStateVariableFilter::setFilterType(const int& newType)
{
	filterType = newType;
}

void VAStateVariableFilter::setCutoffPitch(const float& newCutoffPitch)
{
	cutoffFreq = pitchToFreq(newCutoffPitch);
	calcFilter();
}

void VAStateVariableFilter::setCutoffFreq(const float& newCutoffFreq)
{
	cutoffFreq = newCutoffFreq;
	calcFilter();
}

void VAStateVariableFilter::setResonance(const float& newResonance)
{
	Q = resonanceToQ(newResonance);
	calcFilter();
}

void VAStateVariableFilter::setQ(const float& newQ)
{
	Q = newQ;
	calcFilter();
}

void VAStateVariableFilter::setShelfGain(const float& newGain)
{
	shelfGain = newGain;
	calcFilter();
}

void VAStateVariableFilter::setFilter(const int& newType, const float& newCutoffFreq,
									  const float& newResonance, const float& newShelfGain)
{
	filterType = newType;
	cutoffFreq = newCutoffFreq;
	Q = resonanceToQ(newResonance);
	calcFilter();
}

void VAStateVariableFilter::setSampleRate(const float& newSampleRate)
{
	sampleRate = newSampleRate;
	calcFilter();
}

//==============================================================================
void VAStateVariableFilter::calcFilter(void)
{
	// prewarp the cutoff (for bilinear-transform filters)
	float wd = cutoffFreq * 2.0f * M_PI;
	float T = 1.0f / (float)sampleRate;
	float wa = (2.0f / T) * tan(wd * T / 2.0f);

	gCoeff = wa * T / 2.0f;			// Calculate g (gain element of integrator)

	RCoeff = 1.0f / (2.0f * Q);		// Calculate Zavalishin's R from Q
									// R is referred to as the damping parameter

	KCoeff = shelfGain;				// Gain for BandShelving filter
}

float VAStateVariableFilter::processChannel(const float& input, const int& channelIndex)
{
	float HP = 0.0f;
	HP = (input - (2.0f * RCoeff + gCoeff) * z1_A[channelIndex] - z2_A[channelIndex])
		/ (1.0f + (2.0f * RCoeff * gCoeff) + gCoeff * gCoeff);

	float BP = 0.0f;
	BP = HP * gCoeff + z1_A[channelIndex];

	float LP = 0.0f;
	LP = BP * gCoeff + z2_A[channelIndex];

	float UBP = 0.0f;
	UBP = 2.0f * RCoeff * BP;

	float BShelf = 0.0f;
	BShelf = input + UBP * KCoeff;

	float Notch = 0.0f;
	Notch = input - UBP;

	float AP = 0.0f;
	AP = input - (4.0f * RCoeff * BP);

	float Peak = 0.0f;
	Peak = LP - HP;

	z1_A[channelIndex] = gCoeff * HP + BP;		// unit delay (state variable)
	z2_A[channelIndex] = gCoeff * BP + LP;		// unit delay (state variable)

	// Selects which filter type this function will output.
	switch (filterType) {
	case SVFLowpass:
		return LP;
		break;
	case SVFBandpass:
		return BP;
		break;
	case SVFHighpass:
		return HP;
		break;
	case SVFUnitGainBandpass:
		return UBP;
		break;
	case SVFBandShelving:
		return BShelf;
		break;
	case SVFNotch:
		return Notch;
		break;
	case SVFAllpass:
		return AP;
		break;
	case SVFPeak:
		return Peak;
		break;
	default:
		return 0.0f;
		break;
	}
}

//==============================================================================
