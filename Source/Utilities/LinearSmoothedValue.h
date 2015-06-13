/*
  ==============================================================================

    LinearSmoothedValue.h
    Created: 29 May 2015 7:23:42pm
    Author:  Jordan

  ==============================================================================
*/

#ifndef LINEARSMOOTHEDVALUE_H_INCLUDED
#define LINEARSMOOTHEDVALUE_H_INCLUDED

//==============================================================================

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class LinearSmoothedValue {
public:
    LinearSmoothedValue() noexcept
        : currentValue{ 0 }, target{ 0 }, step{ 0 }, countdown{ 0 }, stepsToTarget{ 0 }
    {
    }

    //------------------------------------------------------------------------------
    void reset(double sampleRate, double fadeLengthMs) noexcept
    {
        const double fadeLengthSeconds = fadeLengthMs * 0.001;

        jassert(sampleRate > 0 && fadeLengthSeconds >= 0);
        stepsToTarget = (int)std::floor(fadeLengthSeconds * sampleRate);
        currentValue = target;
        countdown = 0;
    }

    //------------------------------------------------------------------------------
    void setValue(float newValue) noexcept
    {
        if (target != newValue) {
            target = newValue;
            countdown = stepsToTarget;

            if (countdown <= 0)
                currentValue = target;
            else
                step = (target - currentValue) / (float)countdown;
        }
    }

    //------------------------------------------------------------------------------
    float getNextValue() noexcept
    {
        if (countdown <= 0)
            return target;

        --countdown;
        currentValue += step;
        return currentValue;
    }

    //------------------------------------------------------------------------------

private:
    //==============================================================================
    float currentValue, target, step;
    int countdown, stepsToTarget;

    JUCE_DECLARE_NON_COPYABLE(LinearSmoothedValue)
};

//==============================================================================
#endif  // LINEARSMOOTHEDVALUE_H_INCLUDED
