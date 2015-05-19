/*
  ==============================================================================

	ParameterSmoother.h
	Created: 13 May 2015 12:43:46am
	Author:  Jordan Harris

  ==============================================================================
*/

#ifndef PARAMETERSMOOTHER_H_INCLUDED
#define PARAMETERSMOOTHER_H_INCLUDED

//==============================================================================

#include "DspUtilities.h"
#include <vector>

//==============================================================================
class ParameterSmoother {
public:
	ParameterSmoother();
	~ParameterSmoother();

	void setValue(float value);
	void setTimeMs(float milliseconds);
	void setSampleRate(double newSampleRate);

	//------------------------------------------------------------------------------
	/** Get the last value of the output from processSmoother */
	float getValue();
	
	//------------------------------------------------------------------------------
	/** This should check to see if the parameter has changed or not. It does this by
	checking if there are duplicates between the currentValue and z1 (previous value).
	This returns a boolean and can be used in the condition of an if statement in
	the process loop that contains processSmoother(). In this if statement, you could
	call processSmoother() and anything else needed to update the object that uses
	ParameterSmoother (i.e. updating filter coefficients).
	- true = no duplicates
	- false = duplicates
	*/
	bool shouldUpdate();

	//------------------------------------------------------------------------------
	/** Used to actually smooth the parameter. This function should be called in the
	processing loop of the object the parameter belongs to.
	- smoothedValue should be the variable that holds the value of the parameter.
	Note: smoothedValue is a reference argument so it will directly change
	the variable passed to it.
	*/
	void processSmoother(float& smoothedValue);

private:
	//==============================================================================
	float currentValue;
	float z1;				// state variable (z^-1)
	float output;			// last value from the smoother
	float timeSec;			// time to interpolate between values in seconds

	double sampleRate;

};

//==============================================================================

ParameterSmoother::ParameterSmoother()
{
	currentValue = 0.0f;
	z1 = 0.0f;				// State variable (previous value)
	output = 0.0f;
	timeSec - 0.0f;
}

//------------------------------------------------------------------------------

ParameterSmoother::~ParameterSmoother()
{
}

//------------------------------------------------------------------------------

void ParameterSmoother::setValue(float value)
{
	currentValue = value;
}

//------------------------------------------------------------------------------

void ParameterSmoother::setTimeMs(float milliseconds)
{
	const float seconds = milliseconds * 0.001f;	// convert milliseconds to seconds
	timeSec = seconds;
}

//------------------------------------------------------------------------------

void ParameterSmoother::setSampleRate(double newSampleRate)
{
	sampleRate = newSampleRate;
}

//------------------------------------------------------------------------------

float ParameterSmoother::getValue()
{
	return output;
}

//------------------------------------------------------------------------------
bool ParameterSmoother::shouldUpdate()
{
	// Duplicate filter
	if (currentValue != z1)
		return true;
	else
		return false;
}

//------------------------------------------------------------------------------
void ParameterSmoother::processSmoother(float& smoothedValue)
{
	smoothedValue = (currentValue - z1) * (0.693147 / clipMin(timeSec * sampleRate, 1)) + z1;
	output = smoothedValue;
	z1 = output;
}

//==============================================================================
#endif  // PARAMETERSMOOTHER_H_INCLUDED
