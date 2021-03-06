/*
 ===============================================================================
 
 LUFSMeterAudioProcessorEditor.h
 
 
 This file is part of the LUFS Meter audio measurement plugin.
 Copyright 2011-12 by Klangfreund, Samuel Gaehwiler.
 
 -------------------------------------------------------------------------------
 
 The LUFS Meter can be redistributed and/or modified under the terms of the GNU 
 General Public License Version 2, as published by the Free Software Foundation.
 A copy of the license is included with these source files. It can also be found
 at www.gnu.org/licenses.
 
 The LUFS Meter is distributed WITHOUT ANY WARRANTY.
 See the GNU General Public License for more details.
 
 -------------------------------------------------------------------------------
 
 To release a closed-source product which uses the LUFS Meter or parts of it,
 a commercial license is available. Visit www.klangfreund.com/lufsmeter for more
 information.
 
 ===============================================================================
 */


#ifndef __LUFS_METER_AUDIO_PROCESSOR_EDITOR__
#define __LUFS_METER_AUDIO_PROCESSOR_EDITOR__

#include "../JuceLibraryCode/JuceHeader.h"
#include "Macros.h"
#include "LUFSMeterAudioProcessor.h"
#include "gui/BackgroundGrid.h"
#include "gui/BackgroundGridCaption.h"
#include "gui/BackgroundVerticalLinesAndCaption.h"
#include "gui/LoudnessBar.h"
#include "gui/LoudnessNumeric.h"
#include "gui/LoudnessHistory.h"
#include "gui/PreferencesPane.h"


//==============================================================================
/**
*/
class LUFSMeterAudioProcessorEditor   : public AudioProcessorEditor,
                                        public Timer,
                                        public ButtonListener,
                                        public SliderListener
{
public:
    LUFSMeterAudioProcessorEditor (LUFSMeterAudioProcessor* ownerFilter);
    ~LUFSMeterAudioProcessorEditor();

    //==============================================================================
    /** The standard Juce paint method. */
    void paint (Graphics& g);
    
    void resized ();
    
    void timerCallback ();
    
    /** The ButtonListener method. */
    void buttonClicked (Button* button);
    
    /** The SliderListener method. */
    void sliderValueChanged (Slider* slider);
    
private:
    LUFSMeterAudioProcessor* getProcessor() const;
    void displayPositionInfo (const AudioPlayHead::CurrentPositionInfo& pos);
    
    AudioPlayHead::CurrentPositionInfo lastDisplayedPosition;
    
    /** Shared values. */
    Value momentaryLoudnessValue;
    Value shortTermLoudnessValue;
    Value integratedLoudnessValue;
    
    /** GUI parameters. */
    int distanceBetweenLevelBarAndTop;
    int distanceBetweenLevelBarAndBottom;
    
    BackgroundGrid backgroundGrid;
    BackgroundGridCaption backgroundGridCaption;
    BackgroundVerticalLinesAndCaption backgroundVerticalLinesAndCaption;
    
    /* Level meters. */
    LoudnessBar momentaryLoudnessBar;
    LoudnessBar shortTermLoudnessBar;
    LoudnessBar integratedLoudnessBar;
    
    /* Level values numeric. */
    LoudnessNumeric momentaryLoudnessNumeric;
    LoudnessNumeric shortTermLoudnessNumeric;
    LoudnessNumeric integratedLoudnessNumeric;
    
    /** Level meter captions. */
    Label momentaryLoudnessCaption;
    Label shortTermLoudnessCaption;
    Label integratedLoudnessCaption;
    
    /** Level history graph. */
    LoudnessHistory loudnessHistory;
    
    /** Preferences pane. */
    PreferencesPane preferencesPane;
    bool preferencesPaneVisible;
    int preferencesPaneXPosition;
    const int preferencesPaneYPosition;
    const int preferencesPaneWidth;
    const int preferencesPaneHeight;
    
    Label infoLabel;
    
    TextButton resetButton;
    
    ScopedPointer<ResizableCornerComponent> resizer;    
    /** Specifies the maximum size of the window. */
    ComponentBoundsConstrainer resizeLimits;
};


#endif  // __LUFS_METER_AUDIO_PROCESSOR_EDITOR__
