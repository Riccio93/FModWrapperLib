#include "SoundLibrary.h"
#include <stdexcept>


void SoundLibrary::Initialize(int MaxChannelsNum)
{
	FMOD_RESULT result;

	//Create system
	result = FMOD::System_Create(&system);
	ERRCHECK(result);

	//Initialize system
	//MaxChannelsNum is the max number of virtual channels
	result = system->init(MaxChannelsNum, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);
}

SoundLibrary::Sound SoundLibrary::Load(const char* fileName, LoadMode loadMode)
{
	FMOD_RESULT result;
	Sound sound;

	result = system->createSound(fileName, loadMode, 0, &sound);
	ERRCHECK(result);

	return sound;
}

void SoundLibrary::Play(Sound sound, Channel* channel)
{
	FMOD_RESULT result;
	result = system->playSound(sound, 0, false, channel);
	ERRCHECK(result);
}

void SoundLibrary::TogglePause(Channel channel)
{
	FMOD_RESULT result;
	bool currentPauseValue;
	result = channel->getPaused(&currentPauseValue);
	ERRCHECK(result);
	result = channel->setPaused(!currentPauseValue);
	ERRCHECK(result);
}

void SoundLibrary::SetVolume(Channel channel, float volume)
{
	FMOD_RESULT result;
	result = channel->setVolume(volume);
	ERRCHECK(result);
}

void SoundLibrary::SetPan(Channel channel, float pan)
{
	FMOD_RESULT result;
	result = channel->setPan(pan);
	ERRCHECK(result);
}

bool SoundLibrary::IsPlaying(Channel channel)
{
	FMOD_RESULT result;
	bool bIsPlaying;
	result = channel->isPlaying(&bIsPlaying);
	ERRCHECK(result);
	return bIsPlaying;
}

bool SoundLibrary::IsPaused(Channel channel)
{
	FMOD_RESULT result;
	bool bIsPaused;
	result = channel->getPaused(&bIsPaused);
	ERRCHECK(result);
	return bIsPaused;
}

unsigned int SoundLibrary::GetMilliseconds(Channel channel)
{
	FMOD_RESULT result;
	unsigned int milliseconds;
	result = channel->getPosition(&milliseconds, FMOD_TIMEUNIT_MS);
	ERRCHECK(result);
	return milliseconds;
}

void SoundLibrary::Update()
{
	FMOD_RESULT result;
	result = system->update();
	ERRCHECK(result);
}
