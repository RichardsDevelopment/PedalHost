/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
	// Make sure you set the size of the component after
	// you add any child components.
	setSize(800, 600);

	// Some platforms require permissions to open input channels so request that here
	if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
		&& !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
	{
		RuntimePermissions::request(RuntimePermissions::recordAudio,
			[&](bool granted) { if (granted)  setAudioChannels(2, 2); });
	}
	else
	{
		// Specify the number of input and output channels that we want to open
		setAudioChannels(2, 2);
	}

	pluginFormatManager = std::unique_ptr<AudioPluginFormatManager>(new AudioPluginFormatManager());
	plist = std::unique_ptr<KnownPluginList>(new KnownPluginList());

	pluginFormatManager->addDefaultFormats();
	FileSearchPath toSearch("C:\\Program Files\\REAPER (x64)\\Plugins\\FX\\");

	for (int i = 0; i < pluginFormatManager->getNumFormats(); i++) {
		format = pluginFormatManager->getFormat(0);
		pluginDirectoryScanner = new PluginDirectoryScanner(*plist, *format, toSearch, true, File(), true);

		String plugname;

		while (true)
		{
			parsePluginInfo(pluginDirectoryScanner->getNextPluginFileThatWillBeScanned());
			
			int size = foundPlugins.size();
			DBG("Vector Length: " + std::to_string(size));

			if (pluginDirectoryScanner->scanNextFile(true, plugname) == false)
				break;
		}
	}

	delete pluginDirectoryScanner;

	createListComponent();
	/*

	auto instance = pluginFormatManager.createPluginInstance(*pluginDescriptions[0], 48000, 1024, msg);

	auto editor = instance->createEditor();
	auto bc = editor->getConstrainer();
	editor->setBounds(0, 0, bc->getMinimumWidth(), bc->getMinimumHeight());

	addAndMakeVisible(editor);
	*/
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

	// Get the current active audio device and its active input/ output channels
	auto* device = deviceManager.getCurrentAudioDevice();
	auto activeInputChannels = device->getActiveInputChannels();
	auto activeOutputChannels = device->getActiveOutputChannels();

	// Get maximum number of input/ output channels we must iterate over
	auto maxInputChannels = activeInputChannels.getHighestBit() + 1;
	auto maxOutputChannels = activeOutputChannels.getHighestBit() + 1;

	// Volume level will be 1 * whatever is input
	auto level = 1.0f;

	// For each output channel
	for (auto channel = 0; channel < maxOutputChannels; ++channel)
	{
		// If no active output OR input channel, clear the buffer to output nothing
		if ((!activeOutputChannels[channel]) || maxInputChannels == 0)
		{
			bufferToFill.buffer->clear(channel, bufferToFill.startSample, bufferToFill.numSamples);
		}
		// Else write input to output buffer
		else
		{
			auto actualInputChannel = channel % maxInputChannels; // [1]

			// If no active input channel, clear output buffer to output nothing
			if (!activeInputChannels[channel]) // [2]
			{
				bufferToFill.buffer->clear(channel, bufferToFill.startSample, bufferToFill.numSamples);
			}
			// Else output each sample at appropriate level to the output buffer
			else // [3]
			{
				auto* inBuffer = bufferToFill.buffer->getReadPointer(actualInputChannel,bufferToFill.startSample);
				auto* outBuffer = bufferToFill.buffer->getWritePointer(channel, bufferToFill.startSample);
				for (auto sample = 0; sample < bufferToFill.numSamples; ++sample) {
					outBuffer[sample] = inBuffer[sample] * random.nextFloat() * level;
				}
			}
		}
	}
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}

void MainComponent::parsePluginInfo(String path) 
{
	UserPlugin thisPlugin;
	std::size_t index = path.toStdString().find_last_of("/\\");

	std::string filename = path.toStdString().substr(index + 1);
	thisPlugin.pluginName = filename;

	std::string filepath = path.toStdString().substr(0, index);
	thisPlugin.pluginPath = filepath;

	foundPlugins.push_back(thisPlugin);
}

void MainComponent::createListComponent()
{

}
