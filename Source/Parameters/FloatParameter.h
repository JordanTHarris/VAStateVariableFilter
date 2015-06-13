/*
  ==============================================================================

    FloatParameter.h
    Created: 2 May 2015 4:07:55am
    Author:  Jordan Harris

  ==============================================================================
*/

// This class is used to handle parameter information passed to and from the
// plugin's host. This particular class handles float parameters (32 bit).

#ifndef FLOATPARAMETER_H_INCLUDED
#define FLOATPARAMETER_H_INCLUDED

//==============================================================================

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================

class FloatParameter : public AudioProcessorParameter {
public:
    FloatParameter(float defaultParameterValue, const String& paramName);
    float getValue() const override;
    void setValue(float newValue) override;
    float getDefaultValue() const override;
    String getName(int maximumStringLength) const override;
    String getLabel() const override;
    float getValueForText(const String& text) const override;

private:
    float defaultValue, value;
    String name;
    int index;			// index to check which parameter is used.
};

//==============================================================================
#endif  // FLOATPARAMETER_H_INCLUDED
