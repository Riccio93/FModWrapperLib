#pragma once

#include "fmod.hpp"

#include "common.h"



enum LoadMode
{
	LOAD_DEFAULT = FMOD_DEFAULT,
	STATIC = FMOD_CREATESAMPLE,
	STREAMING = FMOD_CREATESTREAM
};

enum SoundMode
{
	SOUND_DEFAULT = FMOD_DEFAULT,
	ONE_SHOT = FMOD_LOOP_OFF,
	LOOP = FMOD_LOOP_NORMAL,
};

class SoundLibrary
{

public:

	//Type aliases definitions
	using Sound = FMOD::Sound*;
	using Channel = FMOD::Channel*;

	//Functions ------------------------------------------------------------------------

	//Initializes the system
	void Initialize(int MaxChannels);

	//Loads an audio file
	Sound Load(const char* fileName, LoadMode loadMode = LoadMode::LOAD_DEFAULT);

	//Plays an audio file on the selected channel
	void Play(Sound sound, Channel* channel);

	//Toggles pause on and off on the selected channel
	void TogglePause(Channel channel);

	//Sets the volume (0 mute, 1 max volume)
	void SetVolume(Channel channel, float volume);

	void SetPan(Channel channel, float pan);


	FMOD::System* system;
};

