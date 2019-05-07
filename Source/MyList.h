/*
  ==============================================================================

    MyList.h
    Created: 5 May 2019 6:47:20pm
    Author:  Eric

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MyList    : public Component,
				  public TableListBoxModel
{
public:
    MyList();
    ~MyList();

    void paint (Graphics&) override;
    void resized() override;
	Component* CreateRowComponent();


private:
	TableListBox table{ {}, this };
	Font font{ 14.0f };
	int numRows = 0;

	int getNumRows() override{ return numRows; }
	void paintRowBackground(Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) override
	{
		auto alternateColour = getLookAndFeel().findColour(ListBox::backgroundColourId)
			.interpolatedWith(getLookAndFeel().findColour(ListBox::textColourId), 0.03f);
		if (rowIsSelected)
			g.fillAll(Colours::lightblue);
		else if (rowNumber % 2)
			g.fillAll(alternateColour);
	}
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyList)
};
