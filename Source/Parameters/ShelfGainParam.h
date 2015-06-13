/*
  ==============================================================================

    ShelfGainParam.h
    Created: 11 May 2015 11:16:42am
    Author:  Jordan Harris

  ==============================================================================
*/

#ifndef SHELFGAINPARAM_H_INCLUDED
#define SHELFGAINPARAM_H_INCLUDED

//==============================================================================

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "../Effects/VAStateVariableFilter.h"

//==============================================================================

class ShelfGainParam : public FloatParameter {
public:
    ShelfGainParam(VAStateVariableFilter& svfFilter,
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

        stateVariableFilter.setShelfGain(newValue);
    }

private:
    VAStateVariableFilter& stateVariableFilter;
};

//==============================================================================
#endif  // SHELFGAINPARAM_H_INCLUDED
