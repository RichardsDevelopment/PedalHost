/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "structs.h"
#include <string>
#include <filesystem>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
	Random random;
	std::vector<UserPlugin> foundPlugins;
	
	AudioPluginFormat* format;
	PluginDirectoryScanner* pluginDirectoryScanner;
	std::unique_ptr<AudioPluginFormatManager> pluginFormatManager; 
	std::unique_ptr<KnownPluginList> plist;

	void parsePluginInfo(String path);
	void createListComponent();
    
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
