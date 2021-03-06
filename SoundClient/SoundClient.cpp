#include "SoundLibrary.h"

#define MAX_CHANNELS_NUM 8

//Function to clamp volume & pan values in the respective intervals
float Clamp(float x, float lower, float upper)
{
	return min(upper, max(x, lower));
}

int FMOD_Main()
{
    FMOD_RESULT result;

	SoundLibrary system;
	SoundLibrary::Channel channel = 0;
	SoundLibrary::Sound sound1;
	SoundLibrary::Sound sound2;
	SoundLibrary::Sound sound3;
    SoundLibrary::ChannelGroup masterChannelGroup;

	float volume = 1;
	float pan = 0;

    //Init for the console screen (including window dimensions)
	Common_Init(nullptr);
    SetConsoleTitleA("FMOD Wrapper Project");       

    //Initializes the system (param: max number of virtual channels)
    system.Initialize(MAX_CHANNELS_NUM);

    //Loads audio files
    sound1 = system.Load("Media/swish.wav", LoadMode::STATIC);
    sound2 = system.Load("Media/singing.wav", LoadMode::STREAMING);
    sound3 = system.Load("Media/drumloop.wav", LoadMode::STREAMING);

    masterChannelGroup = system.GetMasterChannelGroup();

    //Main Loop    
    do
    {
        //Built-in FMOD function
		Common_Update();

        //INPUT RESPONSES ----------------------------------------------------------------------------

		if (Common_BtnPress(BTN_ACTION1)) // '1' key
		{
			system.Play(sound1, &channel, ONE_SHOT);
		}        

		if (Common_BtnPress(BTN_ACTION2)) // '2' key
		{
			system.Play(sound2, &channel, ONE_SHOT);
		}

		if (Common_BtnPress(BTN_ACTION3)) // '3' key
		{
			system.Play(sound3, &channel, LOOP);
		}

        if (Common_BtnPress(BTN_MORE)) // "Space" key
        {
            system.TogglePauseAll(masterChannelGroup);
        }

        if (Common_BtnPress(BTN_ACTION4)) // '4' key
        {
            system.StopAll(masterChannelGroup);
        }

		if (Common_BtnDown(BTN_DOWN)) // "DOWN" key
		{
			//Makes sure that the volume is always between 0 and 1
			volume = Clamp(volume - 0.1f, 0.f, 1.f);
		}

        if(Common_BtnDown(BTN_UP)) // "UP" key
        {
            //Makes sure that the volume is always between 0 and 1
            volume = Clamp(volume + 0.1f, 0.f, 1.f);
        }	

        if(Common_BtnDown(BTN_LEFT)) // "LEFT" key
        {
            //Makes sure that the pan is always between -1 and 1
            pan = Clamp(pan - 0.1f, -1.f, 1.f);
        }

		if (Common_BtnDown(BTN_RIGHT)) // "RIGHT" key
		{
			//Makes sure that the pan is always between -1 and 1
			pan = Clamp(pan + 0.1f, -1.f, 1.f);
		}

        system.SetVolumeAll(masterChannelGroup, volume);
        system.SetPanAll(masterChannelGroup, pan);

        system.Update();

        //PRINTING ON CONSOLE ---------------------------------------------------------------------

        unsigned int milliseconds = 0;
        unsigned int totalMilliseconds = 0;
        bool bIsPlaying = false;
        bool bIsPaused = false;
        bool bIsGroupPaused = false;
        int activeChannels = system.GetPlayingChannels();
        char progressBar[43] = "|----------------------------------------|";

		if (channel)
		{
			SoundLibrary::Sound currentlyPlaying = 0;
			bIsPlaying = system.IsPlaying(channel);
            bIsPaused = system.IsPaused(channel);
            bIsGroupPaused = system.IsGroupPaused(masterChannelGroup);
            milliseconds = system.GetMilliseconds(channel);
            currentlyPlaying = system.GetCurrentlyPlayingSound(channel);
            totalMilliseconds = system.GetTotalLength(currentlyPlaying);

            if (!bIsPlaying)
            {
                totalMilliseconds = 0;

                //When the channel finishes playing the console view switches to another one (currently active)
                for(int i = 0; i < MAX_CHANNELS_NUM; i++)
                {
                    SoundLibrary::Channel cha;
                    masterChannelGroup->getChannel(i, &cha);

                    if (cha && system.IsPlaying(cha))
                        channel = cha;
                }                
            }
			
			if (bIsPlaying)
			{
				int index = milliseconds * 40 / totalMilliseconds;
				progressBar[index + 1] = '|';
			}
		}

        Common_Draw("#################################################");
        Common_Draw("############ FMOD WRAPPER LIBRARY ###############");
        Common_Draw("############ ANDREA RICCI - UNIVR ###############");
        Common_Draw("#################################################");
        Common_Draw("");
        Common_Draw("Press a key to perform an action:");
        Common_Draw("");
        Common_Draw("%s: Play \"swish\" audio file (Static, one shot)", Common_BtnStr(BTN_ACTION1));
        Common_Draw("%s: Play \"singing\" audio file (Streaming, one shot)", Common_BtnStr(BTN_ACTION2));
        Common_Draw("%s: Play \"drumloop\" audio file (Streaming, loop)", Common_BtnStr(BTN_ACTION3));
        Common_Draw("");
        Common_Draw("%s: Stop", Common_BtnStr(BTN_ACTION4));
        Common_Draw("%s: Pause", Common_BtnStr(BTN_MORE));        
        Common_Draw("%s & %s: Adjust volume", Common_BtnStr(BTN_DOWN), Common_BtnStr(BTN_UP));
        Common_Draw("%s & %s: Adjust pan", Common_BtnStr(BTN_LEFT), Common_BtnStr(BTN_RIGHT));
        Common_Draw("%s: Quit", Common_BtnStr(BTN_QUIT));
        Common_Draw("");
        Common_Draw("Volume : %.1f", volume);
        Common_Draw("Pan : %.1f", pan);
        Common_Draw("");
        Common_Draw("Time: %02d : %02d : %02d / %02d : %02d : %02d", milliseconds / 1000 / 60, 
            milliseconds / 1000 % 60, milliseconds / 10 % 100, totalMilliseconds / 1000 / 60, 
            totalMilliseconds / 1000 % 60, totalMilliseconds / 10 % 100);
        Common_Draw("%s", progressBar);
		if (!bIsPlaying)
			Common_Draw("State: Inactive");
		else
			Common_Draw("State: %s", bIsGroupPaused == true ? "Paused" : "Playing");
        Common_Draw("Channels playing: %d", activeChannels);

        Common_Sleep(50);
    } while (!Common_BtnPress(BTN_QUIT)); // "ESC" key

    //QUITTING ------------------------------------------------------------------------------------

    //Releasing memory
    result = sound1->release();
    ERRCHECK(result);
	result = sound2->release();
	ERRCHECK(result);
	result = sound3->release();
	ERRCHECK(result);

	Common_Close();

	return 0;
}