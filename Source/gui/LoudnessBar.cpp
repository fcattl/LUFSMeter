/*
 ===============================================================================
 
 LoudnessBar.cpp
 
 
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


#include "LoudnessBar.h"


//==============================================================================
LoudnessBar::LoudnessBar (const Value & levelValueToReferTo,
                          const Value & minValueToReferTo,
                          const Value & maxValueToReferTo)
  : currentLevel (minValueToReferTo.getValue()),
    previousLevel (minValueToReferTo.getValue())
{
    levelValue.referTo(levelValueToReferTo);
    levelValue.addListener(this);
    
    minLoudness.referTo(minValueToReferTo);
    minLoudness.addListener(this);
    maxLoudness.referTo(maxValueToReferTo);
    maxLoudness.addListener(this);

    determineStretchAndOffset();
}

LoudnessBar::~LoudnessBar ()
{
    levelValue.removeListener(this);
}

Value & LoudnessBar::getLevelValueObject ()
{
    return levelValue;
}

void LoudnessBar::valueChanged (Value & value)
{
    if (value == levelValue)
    {
        
        currentLevel = value.getValue();
        
        // Ensure that the currentLevel is in the interval
        // [minimumLevel, maximumLevel].
        currentLevel = jmax(currentLevel, float(minLoudness.getValue()));
        currentLevel = jmin(currentLevel, float(maxLoudness.getValue()));
        
        if (currentLevel != previousLevel)
        {
            //        float topBorderInPercent = stretch*jmax(currentLevel,previousLevel) + offset;
            //        float bottomBorderInPercent = stretch*jmin(currentLevel,previousLevel) + offset;
            //        
            //        const int topLeftX = 0;
            //        const int topLeftY = floor((1-topBorderInPercent) * (float) getHeight()) -3;
            //        const int heightOfSectionToDraw = ceil((topBorderInPercent-bottomBorderInPercent) * (float) getHeight()) + 3;
            //        
            previousLevel = currentLevel;
            //    
            //        repaint(topLeftX, topLeftY, getWidth(), heightOfSectionToDraw);
            
            // Mesurements showed that it is more CPU efficient to draw the whole
            // bar and not only the section that has changed.
            repaint();
        }
    }
    else if (value == minLoudness || value == maxLoudness)
    {
        determineStretchAndOffset();
        repaint();
    }
}

//==============================================================================
void LoudnessBar::paint (Graphics& g)
{
    const float width = (float) getWidth();
    const float height = (float) getHeight();
    
    // Draw a background
//    g.setColour(Colours::black);
//    float x = 0.0f;
//    float y = 0.0f;
//    float cornerSize = 3.0f;
//    g.fillRoundedRectangle(x, y, width, height, cornerSize);
    
    float barHeightInPercent = stretch*currentLevel + offset;
    g.setColour(Colours::green);
    const float topLeftX = 0.0f;
    float topLeftY = (1.0f - barHeightInPercent) * height;
    float bottomY = height;
    g.fillRect(topLeftX,
               topLeftY,
               width,
               bottomY-topLeftY);
}

void LoudnessBar::determineStretchAndOffset()
{
    // These two values define a linear mapping
    //    f(x) = stretch * x + offset
    // for which
    //    f(minimumLevel) = 0
    //    f(maximumLevel) = 1
    stretch = 1.0f/(double(maxLoudness.getValue()) - double(minLoudness.getValue()));
    offset = -double(minLoudness.getValue()) * stretch;
}