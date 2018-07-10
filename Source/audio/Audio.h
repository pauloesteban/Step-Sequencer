/*
  ==============================================================================

    Audio.h
    Created: 6 Jul 2018 4:01:38pm
    Author:  Corey Ford

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================

namespace audio
{    
    /**
     * Handles MIDI input and audio output.
     */
    class Audio : public AudioIODeviceCallback,
                  public MidiInputCallback
    {
    public:
        
        /** Constructor. Sets up the audio device manager threads. */
        Audio();
        
        /** Destructor. Removes audio device manager threads. */
        ~Audio();
        
        /**
         *  Called before audio callback starts or whenever the sample rate / frame size changes.
         *  @param the audio device object.
         */
        virtual void audioDeviceAboutToStart (AudioIODevice* device) override;
        
        /**
         *  The processing function iterating over each audio sample of our buffer
         *  modifying by our synthesiser object.
         *
         *  @param inputChannelData is a pointer for our incoming audio
         *  @param numInputChannels is the number of audio input channels avaliable
         *  @param outputChannelData is a pointer to the audio output to our audio device.
         *  @param numOutputChannels is the number of audio channels e.g. 2 for stereo.
         *  @param numSamples is the size of our audio buffer in samples.
         */
        virtual void audioDeviceIOCallback (const float** inputChannelData,
                                            int numInputChannels,
                                            float** outputChannelData,
                                            int numOutputChannels,
                                            int numSamples) override;
        
        /**
         * Called to indicate that the device has stopped.
         */
        virtual void audioDeviceStopped() override;
        
        
        /**
         * Callback function trigger for every midi message recieved.
         * 
         * @param source is the midi input source to be listened to.
         * @param message is the midi message recieved.
         */
        virtual void handleIncomingMidiMessage (MidiInput* source,
                                                const MidiMessage& message) override;
        
    private:
        AudioDeviceManager _audioDeviceManager;
    };
    
} //namespace audio