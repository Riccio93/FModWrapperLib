#include "SoundLibrary.h"
#include <iostream>
#include <conio.h> //For keyboard inputs

int main()
{
	//void* extradriverdata = 0;
	//Common_Init(&extradriverdata);

    SoundLibrary system;
    SoundLibrary::Channel channel = 0;

    SoundLibrary::Sound sound1;

    //Initializes the system
    system.Initialize(32);
    std::cout << "I'm initializing" << std::endl;

    //Loads audio files
    sound1 = system.Load("Media/drumloop.wav", LoadMode::STATIC);
    std::cout << "Audio file loaded" << std::endl;

    int menuChoice = 0;
    //TEST
    do
    {
        //Clears the screen
        std::system("cls");

        std::cout << "WRITING" << std::endl;

        while(_kbhit()) //If a keyboard key is hit...
        {
            wint_t key = _getwch(); //Get the key
            //TODO: ?????
			if (key == 0 || key == 224)
			{
				key = 256 + _getwch(); // Handle multi-char keys
			}
            //Num 1 plays sound 1
            if(key == '1')
            {
                system.Play(sound1, &channel);
            }
        }
        

		/*if (key == '1')    newButtons |= (1 << BTN_ACTION1);
		else if (key == '2')    newButtons |= (1 << BTN_ACTION2);
		else if (key == '3')    newButtons |= (1 << BTN_ACTION3);
		else if (key == '4')    newButtons |= (1 << BTN_ACTION4);
		else if (key == 256 + 75) newButtons |= (1 << BTN_LEFT);
		else if (key == 256 + 77) newButtons |= (1 << BTN_RIGHT);
		else if (key == 256 + 72) newButtons |= (1 << BTN_UP);
		else if (key == 256 + 80) newButtons |= (1 << BTN_DOWN);
		else if (key == 32)     newButtons |= (1 << BTN_MORE);
		else if (key == 27)     newButtons |= (1 << BTN_QUIT);
		else if (key == 112)    gPaused = !gPaused;*/



        /*if(Common_BtnPress(BTN_ACTION1))
        {
            system.Play(sound1, &channel);
        }

        if(Common_BtnPress(BTN_ACTION2))
        {
            system.TogglePause(channel);
        }*/
    } while (true);
    

}
