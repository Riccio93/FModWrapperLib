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

    } while (!Common_BtnPress(BTN_QUIT)); // "ESC" key

	Common_Close();

	return 0;
}