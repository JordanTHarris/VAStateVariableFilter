/*
  ==============================================================================

    KnobLookAndFeel.cpp
    Created: 26 Apr 2015 6:18:25am
    Author:  Jordan Harris

  ==============================================================================
*/

#include "KnobLookAndFeel.h"

//==============================================================================
KnobLookAndFeel::KnobLookAndFeel()
{
    // Load my image here (from Binary Data)
    myStrip = ImageCache::getFromMemory (BinaryData::SilverKnob60_png, BinaryData::SilverKnob60_pngSize);
}

KnobLookAndFeel::~KnobLookAndFeel()
{
}



void KnobLookAndFeel::drawRotarySlider(Graphics& g,
    int x,
    int y,
    int width,
    int height,
    float sliderPosProportional,
    float rotaryStartAngle,
    float rotaryEndAngle,
    Slider& slider)
{
    //value between 0 and 1 for current amount of rotation
    const double fractRotation = (slider.getValue() - slider.getMinimum()) 
                                    / (slider.getMaximum() - slider.getMinimum()); 

    // number of frames for vertical film strip
    const int nFrames = myStrip.getHeight()/myStrip.getWidth(); 

    // current index from 0 --> nFrames-1
    const int frameIdx = (int)ceil(fractRotation * ((double)nFrames-1.0) ); 

    const float radius = jmin (width / 2.0f, height / 2.0f) ;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius;
    const float ry = centreY - radius;

    g.drawImage(myStrip,	
                (int)rx,
                (int)ry,
                2*(int)radius,
                2*(int)radius,   //Dest
                0,
                frameIdx*myStrip.getWidth(),
                myStrip.getWidth(),
                myStrip.getWidth()); //Source
}