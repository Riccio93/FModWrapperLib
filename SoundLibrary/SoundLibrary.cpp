#include "SoundLibrary.h"
#include <stdexcept>


void SoundLibrary::Initialize(int MaxChannelsNum)
{
	FMOD_RESULT result;

	//Create system
	result = FMOD::System_Create(&system);
	if(result != FMOD_RESULT::FMOD_OK)
	{
		throw std::runtime_error("ERROR: Cannot create FMOD system \nError type: " + result);
		return;
	}

	//Initialize system
	//MaxChannelsNum is the max number of virtual channels
	result = system->init(MaxChannelsNum, FMOD_INIT_NORMAL, 0);
	if (result != FMOD_RESULT::FMOD_OK)
	{
		throw std::runtime_error("ERROR: Cannot initialize system \nError type: " + result);
		return;
	}
}

SoundLibrary::Sound SoundLibrary::Load(const char* fileName, LoadMode loadMode)
{
	FMOD_RESULT result;
	Sound sound;

	result = system->createSound(fileName, loadMode, 0, &sound);
	if (result != FMOD_RESULT::FMOD_OK)
	{
		throw std::runtime_error("ERROR: Cannot create sound\nError type: " + result);
		return nullptr;
	}

	return sound;
}

void SoundLibrary::Play(Sound sound, Channel* channel)
{
	FMOD_RESULT result;
	result = system->playSound(sound, 0, false, channel);
	if (result != FMOD_RESULT::FMOD_OK)
	{
		throw std::runtime_error("ERROR: Cannot play audio file\nError type: " + result);
		return;
	}
}

void SoundLibrary::TogglePause(Channel channel)
{
	FMOD_RESULT result;
	bool currentPauseValue;
	result = channel->getPaused(&currentPauseValue);
	if (result != FMOD_RESULT::FMOD_OK)
	{
		throw std::runtime_error("ERROR: Cannot get current pause value\nError type: " + result);
		return;
	}
	result = channel->setPaused(!currentPauseValue);
	if (result != FMOD_RESULT::FMOD_OK)
	{
		throw std::runtime_error("ERROR: Cannot toggle pause value\nError type: " + result);
		return;
	}
}

