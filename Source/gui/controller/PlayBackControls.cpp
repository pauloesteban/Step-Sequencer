/*
  ==============================================================================

    PlayBackControls.cpp
    Created: 6 Jul 2018 7:20:31pm
    Author:  Corey Ford

  ==============================================================================
*/

#include "PlayBackControls.h"

//==============================================================================

namespace gui
{
    PlayBackControls::PlayBackControls()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
        
        addAndMakeVisible(play);
        play.setComponentID("stop");
        play.setButtonText("play");
        play.addListener(&audio::MidiOut::getInstance());
        play.onClick = [this]
        {
            if(play.getComponentID() == "play") ///< components stoppped
            {
                play.setComponentID("stop");
                play.setButtonText("play");
                tempo.setVisible(true);
                velocity.setVisible(true);
                
            }
            else // if componentID == "stop"    ///< components playing
            {
                play.setComponentID("play");
                play.setButtonText("stop");
                tempo.setVisible(false);
                velocity.setVisible(false);
            }
            repaint();
        };
        
        //======================================================================
        
        addAndMakeVisible(tempo);
        tempo.setComponentID("tempo");
        tempo.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
        addAndMakeVisible (tempoLabel);
        tempoLabel.setText ("tempo", dontSendNotification);
        tempoLabel.attachToComponent (&tempo, true);
        tempo.setRange(30.0, 300.0);
        tempo.setValue(120.0);
        tempo.onValueChange = [this]
        {
            audio::MidiOut::getInstance().setPlayback("tempo", tempo.getValue());
        };
        
        //======================================================================
        
        addAndMakeVisible(velocity);
        velocity.setComponentID("velocity");
        velocity.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
        addAndMakeVisible (tempoLabel);
        velocityLabel.setText ("velocity", dontSendNotification);
        velocityLabel.attachToComponent (&velocity, true);
        velocity.setRange(1.0, 127.0);
        velocity.setValue(98.0);
        velocity.onValueChange = [this]
        {
            audio::MidiOut::getInstance().setPlayback("velocity", velocity.getValue());
        };
    }
    
    PlayBackControls::~PlayBackControls(){}
    
    void PlayBackControls::paint (Graphics& g)
    {
        g.fillAll (Colours::crimson);   // clear the background
    }
    
    void PlayBackControls::resized()
    {
        Rectangle<int> playRect = getLocalBounds().removeFromLeft(getLocalBounds().getWidth()
                                                                  / 2.40f);
        
        Rectangle<int> tempoRect = getLocalBounds().removeFromRight(getLocalBounds().getWidth()
                                                                    / 2.0f);
        tempoRect.removeFromTop(getLocalBounds().getHeight() / 2.0f);
        
        Rectangle<int> velocityRect = getLocalBounds().removeFromRight(getLocalBounds().getWidth()
                                                                    / 2.0f);
        velocityRect.removeFromBottom(getLocalBounds().getHeight() / 2.0f);

        play.setBounds (playRect);
        tempo.setBounds (tempoRect);
        velocity.setBounds (velocityRect);
    }
    
}
