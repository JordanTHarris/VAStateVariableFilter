/*
  ==============================================================================

    ResonanceParam.h
    Created: 11 May 2015 11:16:20am
    Author:  Jordan Harris

  ==============================================================================
*/

#ifndef RESONANCEPARAM_H_INCLUDED
#define RESONANCEPARAM_H_INCLUDED

//==============================================================================

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "../Effects/VAStateVariableFilter.h"

//==============================================================================

class ResonanceParam : public FloatParameter {
public:
    ResonanceParam(VAStateVariableFilter& svfFilter,
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

        stateVariableFilter.setResonance(newValue);
    }

private:
    VAStateVariableFilter& stateVariableFilter;
};

//==============================================================================
#endif  // RESONANCEPARAM_H_INCLUDED
