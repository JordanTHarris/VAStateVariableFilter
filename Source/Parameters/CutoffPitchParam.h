/*
  ==============================================================================

    CutoffPitchParam.h
    Created: 11 May 2015 10:54:56am
    Author:  Jordan Harris

  ==============================================================================
*/

#ifndef CUTOFFPITCHPARAM_H_INCLUDED
#define CUTOFFPITCHPARAM_H_INCLUDED

//==============================================================================

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "../Effects/VAStateVariableFilter.h"

//==============================================================================

class CutoffPitchParam : public FloatParameter {
public:
    CutoffPitchParam(VAStateVariableFilter& svfFilter,
                    float defaultParamVal, 
                    const String& paramName)
        : FloatParameter(defaultParamVal, paramName),
          stateVariableFilter{ svfFilter }
    {
    }

    void setValue(float newValue) override
    {
        // call the base class
        FloatParameter::setValue(newValue);

        // change cutoff in pitch values (MIDI) rather than frequency
        stateVariableFilter.setCutoffPitch(newValue);	
    }

private:
    VAStateVariableFilter& stateVariableFilter;
};

//==============================================================================
#endif  // CUTOFFPITCHPARAM_H_INCLUDED
