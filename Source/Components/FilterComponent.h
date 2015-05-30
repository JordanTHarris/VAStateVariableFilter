/*
  ==============================================================================

	FilterComponent.h
	Created: 20 May 2015 2:02:40am
	Author:  Jordan

  ==============================================================================
*/

#include "JuceHeader.h"
#include "TransDirectFormIIFilter.h"

#ifndef FILTERCOMPONENT_H_INCLUDED
#define FILTERCOMPONENT_H_INCLUDED

class FilterComponent : public Component, SliderListener {
public:
	FilterComponent(int resolution);
	~FilterComponent();

	float getPercentForMidiNote(float midi_note);
	void resetResponsePath();
	void computeFilterCoefficients();
	void setFilterSettingsFromPosition(Point<int> position);
	void sliderValueChanged(Slider* moved_slider) override;

	void setResonanceSlider(Slider* slider);
	void setCutoffSlider(Slider* slider);
	void setFilterTypeSlider(Slider* slider);

	void paint(Graphics& g);
	void resized();
	void mouseDown(const MouseEvent& e);
	void mouseDrag(const MouseEvent& e);

private:
	Path filterResponsePath;
	int resolution;

	TransDirectFormIIFilter directFormFilter{ bq_type_lowpass, 1000.0, 0.5, 0.0 };

	ScopedPointer<Slider> filterTypeSlider;
	ScopedPointer<Slider> cutoffSlider;
	ScopedPointer<Slider> resonanceSlider;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FilterComponent)
};



#endif  // FILTERCOMPONENT_H_INCLUDED
