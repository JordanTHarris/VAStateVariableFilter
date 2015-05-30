/*
  ==============================================================================

	FilterComponent.cpp
	Created: 20 May 2015 2:02:40am
	Author:  Jordan

  ==============================================================================
*/

#include "FilterComponent.h"
#include "../Utilities/DspUtilities.h"

#define MAG_TO_DB_CONSTANT 20.0f
#define MIN_GAIN_DB -30.0f
#define MAX_GAIN_DB 24.0f
#define MIN_RESONANCE 0.5
#define MAX_RESONANCE 16.0
#define GRID_CELL_WIDTH 8

#define CLAMP(v, s, b) ((v) < (s) ? (s) : ((v) > (b) ? (b) : (v)))
#define INTERPOLATE(s, e, f) ((s) + (f) * ((e) - (s)))

FilterComponent::FilterComponent(int resolution)
	 
{
	resolution = resolution;
	cutoffSlider = nullptr;
	resonanceSlider = nullptr;
	filterTypeSlider = nullptr;

	directFormFilter.setSampleRate(44100);
	resetResponsePath();

	setOpaque(true);
	setBufferedToImage(true);
}

FilterComponent::~FilterComponent() { }

void FilterComponent::paint(Graphics& g) {
	static const PathStrokeType stroke(1.5f, PathStrokeType::beveled, PathStrokeType::rounded);
	static const DropShadow shadow(Colour(0xbb000000), 5, Point<int>(0, 0));
	g.fillAll(Colour(0xff424242));
	g.setColour(Colour(0xff4a4a4a));
	for (int x = 0; x < getWidth(); x += GRID_CELL_WIDTH)
		g.drawLine(x, 0, x, getHeight());
	for (int y = 0; y < getHeight(); y += GRID_CELL_WIDTH)
		g.drawLine(0, y, getWidth(), y);

	shadow.drawForPath(g, filterResponsePath);

	g.setColour(Colour(0xff565656));
	g.fillPath(filterResponsePath);

	g.setColour(Colour(0xff03a9f4));
	g.strokePath(filterResponsePath, stroke);
}

void FilterComponent::resized() {
	computeFilterCoefficients();
	resetResponsePath();
}

void FilterComponent::mouseDown(const MouseEvent& e) {
	if (e.mods.isRightButtonDown() && filterTypeSlider) {
		int max = filterTypeSlider->getMaximum();
		int current_value = filterTypeSlider->getValue();
		filterTypeSlider->setValue((current_value + 1) % (max + 1));

		computeFilterCoefficients();
	}
	else
		setFilterSettingsFromPosition(e.getPosition());
	repaint();
}

void FilterComponent::mouseDrag(const MouseEvent& e) {
	if (!e.mods.isRightButtonDown()) {
		setFilterSettingsFromPosition(e.getPosition());
		repaint();
	}
}

float FilterComponent::getPercentForMidiNote(float midi_note) {
	float frequency = pitchToFreq(midi_note);
	float response = fabs(directFormFilter.getAmplitudeResponse(frequency));
	float gain_db = MAG_TO_DB_CONSTANT * log10(response);
	return (gain_db - MIN_GAIN_DB) / (MAX_GAIN_DB - MIN_GAIN_DB);
}

void FilterComponent::resetResponsePath() {
	static const int wrap_size = 10;

	if (cutoffSlider == nullptr)
		return;

	filterResponsePath.clear();
	filterResponsePath.startNewSubPath(-wrap_size, getHeight() + wrap_size);
	float start_percent = getPercentForMidiNote(0.0);
	filterResponsePath.lineTo(-wrap_size, getHeight() * (1.0f - start_percent));

	for (int i = 0; i < resolution; ++i) {
		float t = (1.0f * i) / (resolution - 1);
		float midi_note = cutoffSlider->proportionOfLengthToValue(t);
		float percent = getPercentForMidiNote(midi_note);

		filterResponsePath.lineTo(getWidth() * t, getHeight() * (1.0f - percent));
	}

	float end_percent = getPercentForMidiNote(cutoffSlider->getMaximum());

	filterResponsePath.lineTo(getWidth() + wrap_size, getHeight() * (1.0f - end_percent));
	filterResponsePath.lineTo(getWidth() + wrap_size, getHeight() + wrap_size);
}

void FilterComponent::computeFilterCoefficients() {
	if (cutoffSlider == nullptr || resonanceSlider == nullptr || filterTypeSlider == nullptr)
		return;

	int type = static_cast<int>(filterTypeSlider->getValue());
	double frequency = pitchToFreq(cutoffSlider->getValue());
	directFormFilter.setCutoff(frequency);
	double resonance = resonanceToQ(resonanceSlider->getValue());
	directFormFilter.setResonance(resonance);
	double decibals = INTERPOLATE(MIN_GAIN_DB, MAX_GAIN_DB, resonanceSlider->getValue());
	double gain = dbToGain(decibals);
	directFormFilter.setPeakGain(gain);
	//filter.computeCoefficients(type, frequency, resonance, gain);
	resetResponsePath();
}

void FilterComponent::setFilterSettingsFromPosition(Point<int> position) {
	if (cutoffSlider) {
		double percent = CLAMP((1.0 * position.x) / getWidth(), 0.0, 1.0);
		double frequency = cutoffSlider->proportionOfLengthToValue(percent);
		cutoffSlider->setValue(frequency);
	}
	if (resonanceSlider) {
		double percent = CLAMP(1.0 - (1.0 * position.y) / getHeight(), 0.0, 1.0);
		resonanceSlider->setValue(resonanceSlider->proportionOfLengthToValue(percent));
	}

	computeFilterCoefficients();
}

void FilterComponent::sliderValueChanged(Slider* moved_slider) {
	computeFilterCoefficients();
	repaint();
}

void FilterComponent::setResonanceSlider(Slider* slider) {
	if (resonanceSlider)
		resonanceSlider->removeListener(this);
	resonanceSlider = slider;
	resonanceSlider->addListener(this);
	computeFilterCoefficients();
	repaint();
}

void FilterComponent::setCutoffSlider(Slider* slider) {
	if (cutoffSlider)
		cutoffSlider->removeListener(this);
	cutoffSlider = slider;
	cutoffSlider->addListener(this);
	computeFilterCoefficients();
	repaint();
}

void FilterComponent::setFilterTypeSlider(Slider* slider) {
	if (filterTypeSlider)
		filterTypeSlider->removeListener(this);
	filterTypeSlider = slider;
	filterTypeSlider->addListener(this);
	computeFilterCoefficients();
	repaint();
}
