#include "SoundLibrary.h"
#include <iostream>
#include <conio.h> //For keyboard inputs

float Clamp(float x, float lower, float upper)
{
	return min(upper, max(x, lower));
}

int FMOD_Main()
{
    //Init for the command prompt screen (dimensions)
	Common_Init(nullptr);

    SetConsoleTitleA("FMOD Wrapper Project");    

    SoundLibrary system;
    //TODO: Do something with channels???
    SoundLibrary::Channel channel = 0;

    SoundLibrary::Sound sound1;
    SoundLibrary::Sound sound2;
    SoundLibrary::Sound sound3;

    //Initializes the system
    system.Initialize(32);
    float volume = 1;
    float pan = 0;

    //Loads audio files
    sound1 = system.Load("Media/drumloop.wav", LoadMode::STATIC);
    sound2 = system.Load("Media/jaguar.wav", LoadMode::STATIC);
    sound3 = system.Load("Media/swish.wav", LoadMode::STATIC);	

    //Main Loop

    do
    {
        //Built-in function
		Common_Update();

		//Set input responses
		if (Common_BtnPress(BTN_ACTION1)) // '1' key
		{
			system.Play(sound1, &channel);
		}

		if (Common_BtnPress(BTN_ACTION2)) // '2' key
		{
			system.Play(sound2, &channel);
		}

		if (Common_BtnPress(BTN_ACTION3)) // '3' key
		{
			system.Play(sound3, &channel);
		}

        if(Common_BtnPress(BTN_MORE)) // "Space" key
        {
            system.TogglePause(channel);
        }

		if (Common_BtnPress(BTN_DOWN)) // "DOWN" key
		{
			//Makes sure that the volume is always between 0 and 1
			volume = Clamp(volume - 0.1f, 0.f, 1.f);
			system.SetVolume(channel, volume);
		}

        if(Common_BtnPress(BTN_UP)) // "UP" key
        {
            //Makes sure that the volume is always between 0 and 1
            volume = Clamp(volume + 0.1f, 0.f, 1.f);
            system.SetVolume(channel, volume);
        }	

        if(Common_BtnPress(BTN_LEFT)) // "LEFT" key
        {
            //Makes sure that the pan is always between -1 and 1
            pan = Clamp(pan - 0.1f, -1.f, 1.f);
            system.SetPan(channel, pan);
        }

		if (Common_BtnPress(BTN_RIGHT)) // "RIGHT" key
		{
			//Makes sure that the pan is always between -1 and 1
			pan = Clamp(pan + 0.1f, -1.f, 1.f);
			system.SetPan(channel, pan);
		}

        //TODO: Add more functionalities (especially with channels)

        system.Update();




        //PRINTING ON PROMPT

        unsigned int milliseconds = 0;
        unsigned int totalMilliseconds = 0;
        bool bIsPlaying = false;
        bool bIsPaused = false;

		if (channel)
		{
			SoundLibrary::Sound currentSound = 0;
			bIsPlaying = system.IsPlaying(channel);
            bIsPaused = system.IsPaused(channel);
            milliseconds = system.GetMilliseconds(channel);
		}

        Common_Draw("#################################################");
        Common_Draw("############ FMOD WRAPPER PROJECT ###############");
        Common_Draw("#################################################");
        Common_Draw("");
        Common_Draw("Press a key to perform an action:");
        Common_Draw("");
        Common_Draw("%s: Play the \"drumloop\" sound", Common_BtnStr(BTN_ACTION1));
        Common_Draw("%s: Play the \"jaguar\" sound", Common_BtnStr(BTN_ACTION2));
        Common_Draw("%s: Play the \"swish\" sound", Common_BtnStr(BTN_ACTION3));
        Common_Draw("%s & &s: Adjust volume", Common_BtnStr(BTN_DOWN), Common_BtnStr(BTN_UP));
        Common_Draw("%s & &s: Adjust pan", Common_BtnStr(BTN_LEFT), Common_BtnStr(BTN_RIGHT));
        Common_Draw("%s: Quit", Common_BtnStr(BTN_QUIT));
        Common_Draw("");
        Common_Draw("Volume : %.1f", volume);
        Common_Draw("Pan : %.1f", pan);
        Common_Draw("");
        Common_Draw("Time: %02d : %02d : %02d / %02d : %02d : %02d", milliseconds / 1000 / 60, milliseconds / 1000 % 60, milliseconds / 10 % 100, totalMilliseconds / 1000 / 60, totalMilliseconds / 1000 % 60, totalMilliseconds / 10 % 100);


    } while (!Common_BtnPress(BTN_QUIT)); // "ESC" key

	Common_Close();

	return 0;
}