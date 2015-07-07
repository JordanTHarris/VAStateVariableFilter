/*
  ==============================================================================

    FilterTypeParam.h
    Created: 11 May 2015 11:17:15am
    Author:  Jordan Harris

  ==============================================================================
*/

#ifndef FILTERTYPEPARAM_H_INCLUDED
#define FILTERTYPEPARAM_H_INCLUDED

//==============================================================================

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FloatParameter.h"
#include "../Effects/VAStateVariableFilter.h"

//==============================================================================

class FilterTypeParam : public FloatParameter {
public:
    FilterTypeParam(VAStateVariableFilter& svfFilter,
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

        stateVariableFilter.setFilterType(static_cast<int>(newValue));
    }

private:
    VAStateVariableFilter& stateVariableFilter;
};

//==============================================================================
#endif  // FILTERTYPEPARAM_H_INCLUDED
