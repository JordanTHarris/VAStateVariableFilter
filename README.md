# VAStateVariableFilter

To use this filter, check out [this fork](https://github.com/michaeldonovan/VAStateVariableFilter) from [michaeldonovan](https://github.com/michaeldonovan).

#### Analog Circuit Diagram
![Analog Diagram](https://cloud.githubusercontent.com/assets/11206202/7587209/aa5c434a-f882-11e4-9e90-2220cf9cf514.png)

#### Digital TPT Version Block Diagram
![Digital Diagram](https://cloud.githubusercontent.com/assets/11206202/7587264/efe8f322-f882-11e4-80bf-68c6b6fda8f1.png)
------

Virtual analog (VA) State Variable Filter (SVF) that has 8 different types of filter outputs.

This is a plugin made with the JUCE framework, used for creating and testing the State Variable Filter design.

This filter's design comes from **Chapter 5: 2-pole filters | 5.2 Linear digital model** of the book:

	The Art of VA Filter Design
		Vadim Zavalishin
	 rev. 1.0.3 (June 1, 2012)
 
-------
##### The _VAStateVariableFilter_ class has the following 8 output types:
1. Lowpass (LP)
2. Bandpass (BP)
3. Highpass (HP)
4. Unit Gain Bandpass
5. Band Shelving
6. Notch
7. Allpass
8. Peak

------	
##### Using the _VAStateVariableFilter_ class in a JUCE application:
In order to use this class, you will first need to include these files found in the directory.
You may also have to change the #include path(s) to wherever you put DspUtilities:

    VAStateVariableFilter.cpp
    VAStateVariableFilter.h
    DspUtilities.h
    
    
* Create a *VAStateVariableFilter* object in your AudioProcessor class. 

* Initialize the values with reasonable default values in the AudioProcessor's constructor 
  (maybe setting the default for some parameter).
  
* Give the filter the apps sample rate through **VAStateVariableFilter::setSampleRate()**
  in the _AudioProcessor::prepareToPlay()_ function.
  
* In the _AudioProcessor::processBlock()_ function, process the audio buffer through 
  **VAStateVariableFilter::processChannel()**. Pass the sample data to the **_input_**
  argument and the channel's index to the **_channelIndex_** argument.
  
* The filter's parameters can be changed with the following functions:
    * setFilterType()
        * Change the path that the filter outputs, which are different types
    * setCutoffPitch()
        * Change the cutoff logarithmically by pitch values (MIDI note #).    
    * setCutoffFreq()
        * Change the cutoff linearly by frequency values (Hz)
    * setResonance()
        * Sets the resonance with a 0->1 range. This is converted to Q values.
    * setQ()
        * Sets the filter's Q amount.
    * setShelfGain()
        * Sets the shelf gain, used only by the Band Shelving filter output
    * setFilter() 
        * Statically set all of the filter's parameters
