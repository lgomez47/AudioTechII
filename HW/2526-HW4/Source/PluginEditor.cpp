/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
_2526HW4AudioProcessorEditor::_2526HW4AudioProcessorEditor (_2526HW4AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    // get apvts ref
    auto& apvts = audioProcessor.apvts;

    // quick set up for sliders
    auto setupSlider = [](juce::Slider& s)
        {
            s.setSliderStyle(juce::Slider::Rotary);
            s.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 60, 20);
        };

    setupSlider(delaySlider);
    setupSlider(mixSlider);
    setupSlider(feedbackSlider);


    // components
    addAndMakeVisible(delayGroup);

    addAndMakeVisible(delaySlider);
    addAndMakeVisible(mixSlider);
    addAndMakeVisible(feedbackSlider);



    // labels
    auto setupLabel = [](juce::Label& l, const juce::String& text)
        {
            l.setText(text, juce::dontSendNotification);
            l.setJustificationType(juce::Justification::centred);
            l.setColour(juce::Label::textColourId, ColoursTheme::text);
        };

    setupLabel(delayLabel, "Delay");
    setupLabel(mixLabel, "Mix");
    setupLabel(feedbackLabel, "Feedback");

    addAndMakeVisible(delayLabel);
    addAndMakeVisible(mixLabel);
    addAndMakeVisible(feedbackLabel);


    // attachments
    delayAttach = std::make_unique<SliderAttachment>(apvts, "delay", delaySlider);
    mixAttach = std::make_unique<SliderAttachment>(apvts, "mix", mixSlider);
    feedbackAttach = std::make_unique<SliderAttachment>(apvts, "feedback", feedbackSlider);


}


_2526HW4AudioProcessorEditor::~_2526HW4AudioProcessorEditor()
{
}

//==============================================================================
void _2526HW4AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    auto area = getLocalBounds().reduced(10);

    auto top = area.removeFromTop(area.getHeight() / 2);

    g.setColour(ColoursTheme::panel);
    g.fillRoundedRectangle(top.toFloat(), 10.0f);
    g.fillRoundedRectangle(area.toFloat(), 10.0f);

    delayGroup.setColour(juce::GroupComponent::outlineColourId, ColoursTheme::accent);
    delayGroup.setColour(juce::GroupComponent::textColourId, ColoursTheme::text);


    styleSlider(delaySlider);
    styleSlider(mixSlider);
    styleSlider(feedbackSlider);


}

void _2526HW4AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto area = getLocalBounds().reduced(10);

    auto top = area.removeFromTop(area.getHeight() / 2);
    
    delayGroup.setBounds(top);
    auto delayArea = top.reduced(10);

    delaySlider.setBounds(delayArea.removeFromLeft(100).reduced(0, 10));
    mixSlider.setBounds(delayArea.removeFromLeft(100).reduced(0, 10));
    feedbackSlider.setBounds(delayArea.removeFromLeft(100).reduced(0, 10));


    // labels
    delayLabel.setBounds(delaySlider.getX(), delaySlider.getBottom(), 100, 20);
    mixLabel.setBounds(mixSlider.getX(), mixSlider.getBottom(), 100, 20);
    feedbackLabel.setBounds(feedbackSlider.getX(), feedbackSlider.getBottom(), 100, 20);
}

void _2526HW4AudioProcessorEditor::styleSlider(juce::Slider& s)
{
    s.setColour(juce::Slider::rotarySliderFillColourId, ColoursTheme::accent);
    s.setColour(juce::Slider::thumbColourId, ColoursTheme::accent);
    s.setColour(juce::Slider::rotarySliderOutlineColourId, ColoursTheme::knob);
    s.setColour(juce::Slider::textBoxTextColourId, ColoursTheme::text);
    s.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
}
