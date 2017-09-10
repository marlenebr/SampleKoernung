/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
GranularSynthesisAudioProcessorEditor::GranularSynthesisAudioProcessorEditor (GranularSynthesisAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p), Thread("DataLoadingThread")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

	addAndMakeVisible(openFileChooderButton);
	openFileChooderButton.setButtonText("Open...");
	openFileChooderButton.addListener(this);
	//for Thread
	//formatManager.registerBasicFormats();
	startThread();
	//String path = "C:\\000Daten\\eigene_samples\\2017\\08\\2sectest.wav";
	//processor.loadAudioFile(path);

    setSize (400, 300);

}

GranularSynthesisAudioProcessorEditor::~GranularSynthesisAudioProcessorEditor()
{
}


void GranularSynthesisAudioProcessorEditor::run()
{

}

void GranularSynthesisAudioProcessorEditor::buttonClicked(Button* button)
{
	if (button == &openFileChooderButton) selectSampleFile();
}

void GranularSynthesisAudioProcessorEditor::selectSampleFile()
{
	FileChooser chooser("Select a File to open...",
		File::nonexistent,
		"*.wav", "*.aif", "*.aiff");

	if (chooser.browseForFileToOpen()) {
		const File file(chooser.getResult());
		String path(file.getFullPathName());
		swapVariables(processor.chosenPath, path);
	}
}
//
//void GranularSynthesisAudioProcessorEditor::loadAudioFile(String path)
//{
//	const File file(path);
//
//	//Pointer auf Reader und Audiosamples mit der ScopedPointer Klasse, welche das mit den Pointern einfacher macht
//	ScopedPointer<AudioFormatReader> reader(formatManager.createReaderFor(file));
//	//ScopedPointer<AudioSampleBuffer> newBuffer = new AudioSampleBuffer(reader->numChannels, reader->lengthInSamples); //Audiobuffer mit den gleichen einstellungen einstellungen wie die file
//	if (reader != nullptr)
//	{
//		const double duration = reader->lengthInSamples / reader->sampleRate;
//
//		if (duration < 2)
//		{
//			ReferenceCountedBuffer::Ptr newBuffer = new ReferenceCountedBuffer(file.getFileName(),
//				reader->numChannels,
//				reader->lengthInSamples);
//
//			reader->read(newBuffer->getAudioSampleBuffer(), 0, reader->lengthInSamples, 0, true, true);
//			fileBuffer = newBuffer;
//			buffers.add(newBuffer);
//		}
//		else
//		{
//			// handle the error that the file is 2 seconds or longer..
//		}
//	}
//
//
//	//std::cout << "samples in buffer: " << newBuffer->getAudioSampleBuffer()->getNumSamples() << std::endl;
//	//fileBuffer = newBuffer;
//
//
//}

//==============================================================================
void GranularSynthesisAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), Justification::centred, 1);
}

void GranularSynthesisAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

	openFileChooderButton.setBounds(10, 10, 120, 20);
}

//Laden Einer Vorhandenen Audiodatei


//void GranularSynthesisAudioProcessorEditor::read(AudioSampleBuffer* buffer,
//	int startSample,
//	int numSamples,
//	int64 readerStartSample,
//	bool useReaderLeftChan,
//	bool useReaderRightChan)
//{
//
//
//}
