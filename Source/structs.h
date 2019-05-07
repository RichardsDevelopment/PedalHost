/*
  ==============================================================================

    structs.h
    Created: 30 Apr 2019 4:31:56pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <filesystem>
#include <string>

struct UserPlugin {
	std::string pluginPath;
	std::string pluginName;
};