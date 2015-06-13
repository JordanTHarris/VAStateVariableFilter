/*
  ==============================================================================

    KnobLookAndFeel.h
    Created: 26 Apr 2015 6:18:25am
    Author:  Jordan Harris

  ==============================================================================
*/

#ifndef KNOBLOOKANDFEEL_H_INCLUDED
#define KNOBLOOKANDFEEL_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"
#include "SilverKnobBin.h"

//==============================================================================
/*
*/
class KnobLookAndFeel    : public LookAndFeel_V3
{
public:
    KnobLookAndFeel();
    virtual ~KnobLookAndFeel();

    virtual void drawRotarySlider(Graphics& g,
                                    int x,
                                    int y,
                                    int width,
                                    int height,
                                    float sliderPosProportional,
                                    float rotaryStartAngle,
                                    float rotaryEndAngle,
                                    Slider& slider);

private:
    Image verticalSliderKnob;
    Image myStrip;
    int singleImageWidth;
    int singleImageHeight;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobLookAndFeel)
};


#endif  // KNOBLOOKANDFEEL_H_INCLUDED
