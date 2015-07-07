/*
  ==============================================================================

    FloatParameter.cpp
    Created: 2 May 2015 4:07:55am
    Author:  Jordan Harris

  ==============================================================================
*/

// This class is used to handle parameter information passed to and from the
// plugin's host. This particular class handles float parameters (32 bit).

//==============================================================================

#include "FloatParameter.h"

//==============================================================================

FloatParameter::FloatParameter(float defaultParameterValue, const String& paramName)
    : defaultValue{ defaultParameterValue },
      value{ defaultParameterValue },
      name{ paramName }
{
}


float FloatParameter::getValue() const
{
    return value;
}

void FloatParameter::setValue(float newValue)
{
    value = newValue;
}

float FloatParameter::getDefaultValue() const
{
    return defaultValue;
}

String FloatParameter::getName(int maximumStringLength) const
{
    return name.substring(0, maximumStringLength);
}

String FloatParameter::getLabel() const
{
    return String();	// use to return label for parameter's unit (Hz, dB, etc.)
}

float FloatParameter::getValueForText(const String& text) const
{
    return text.getFloatValue();
}

//==============================================================================
