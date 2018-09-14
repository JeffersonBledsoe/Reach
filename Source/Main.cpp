/*
  ==============================================================================

  Main.cpp
  Created: 18 Jan 2018 2:04:28pm
  Author:  Niccolò

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ReachLookAndFeel.h"
#include "MainComponent.h"
#include "LeapLogger.h"

//==============================================================================
class ReachApplication : public JUCEApplication
{
public:
    //==============================================================================
	ReachApplication() = default;
    ~ReachApplication() = default;

    const String getApplicationName() override { return ProjectInfo::projectName; }
    const String getApplicationVersion() override { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override { return true; }

    //==============================================================================
    void initialise (const String& commandLine) override
    {
        ignoreUnused (commandLine);

        LookAndFeel::setDefaultLookAndFeel (&LAF);

		mainWindow = std::make_unique<MainWindow>("Reach");	

		auto desktopFile = File::getSpecialLocation (File::SpecialLocationType::userDesktopDirectory)
				                       .getChildFile(getApplicationName() + String("Log.csv"));
        
		logger = std::make_unique<LeapLogger> (desktopFile);

		Logger::setCurrentLogger(&logger->getLogger());

		logger->startLogger();
    }

    void shutdown() override
    {
        mainWindow = nullptr;

		Logger::setCurrentLogger(nullptr);

		logger.reset();
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        quit();
    }

    void anotherInstanceStarted(const String& commandLine) override
    { }

    class MainWindow : public DocumentWindow
    {
    public:
        MainWindow(StringRef name) : DocumentWindow (name, Desktop::getInstance().getDefaultLookAndFeel()
                                                                                 .findColour (ResizableWindow::backgroundColourId),
                                                                                              DocumentWindow::allButtons)
        {
            setResizable (true, true);
            setUsingNativeTitleBar (true);
            setContentOwned (new MainContentComponent (), true);

            centreWithSize (getWidth(), getHeight());
            setVisible (true);
        }

        void closeButtonPressed() override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:

    std::unique_ptr<MainWindow> mainWindow;
	std::unique_ptr<LeapLogger> logger;

    ReachLookAndFeel LAF;
};

//==============================================================================
START_JUCE_APPLICATION (ReachApplication)
