#include "SoundLibrary.h"

FMOD_RESULT result;

void SoundLibrary::Initialize(int MaxChannelsNum)
{
	//Create system
	result = FMOD::System_Create(&system);
	ERRCHECK(result);

	//Initialize system
	//MaxChannelsNum is the max number of virtual channels
	result = system->init(MaxChannelsNum, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);
}

//Loads an audio file (STATIC or STREAMING depending on loadMode)
SoundLibrary::Sound SoundLibrary::Load(const char* fileName, LoadMode loadMode)
{
	Sound sound;

	result = system->createSound(fileName, loadMode, 0, &sound);
	ERRCHECK(result);

	return sound;
}

//Plays an audio file on the selected channel (looping depending on soundMode, ONE_SHOT or LOOP)
void SoundLibrary::Play(Sound sound, Channel* channel, SoundMode soundMode)
{
	result = sound->setMode(soundMode);
	ERRCHECK(result);
	result = system->playSound(sound, 0, false, channel);
	ERRCHECK(result);
}

//Stops the audio file on the selected channel
void SoundLibrary::Stop(Channel channel)
{
	result = channel->stop();
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
}

//Toggles pause on and off on the selected channel
void SoundLibrary::TogglePause(Channel channel)
{
	bool currentPauseValue;
	result = channel->getPaused(&currentPauseValue);
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
	result = channel->setPaused(!currentPauseValue);
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
}

//Sets the volume (0 mute, 1 max volume)
void SoundLibrary::SetVolume(Channel channel, float volume)
{
	result = channel->setVolume(volume);
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
}

//Sets the pan (-1 left, 0 center, 1 right)
void SoundLibrary::SetPan(Channel channel, float pan)
{
	result = channel->setPan(pan);
	if (result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
}

//Returns if the selected channel is playing something
bool SoundLibrary::IsPlaying(Channel channel)
{
	bool bIsPlaying;
	result = channel->isPlaying(&bIsPlaying);
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
	return bIsPlaying;
}

//Returns if the selected channel is paused
bool SoundLibrary::IsPaused(Channel channel)
{
	bool bIsPaused;
	result = channel->getPaused(&bIsPaused);
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
	return bIsPaused;
}

//Gets milliseconds from the start of the audio file
unsigned int SoundLibrary::GetMilliseconds(Channel channel)
{
	unsigned int milliseconds;
	result = channel->getPosition(&milliseconds, FMOD_TIMEUNIT_MS);
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
	return milliseconds;
}

//Gets total audio file length in milliseconds
unsigned int SoundLibrary::GetTotalLength(Sound sound)
{
	unsigned int totalLength;
	result = sound->getLength(&totalLength, FMOD_TIMEUNIT_MS);
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
	return totalLength;
}

//Returns the sound currently playing on the selected channel
SoundLibrary::Sound SoundLibrary::GetCurrentlyPlayingSound(Channel channel)
{
	Sound currentlyPlaying = nullptr;
	result = channel->getCurrentSound(&currentlyPlaying);
	if(result != FMOD_ERR_INVALID_HANDLE)
		ERRCHECK(result);
	return currentlyPlaying;
}

//Returns the number of the currently active channels
int SoundLibrary::GetPlayingChannels()
{
	int activeChannels;
	result = system->getChannelsPlaying(&activeChannels);
	ERRCHECK(result);
	return activeChannels;
}

//Calls the built-in system.Update
void SoundLibrary::Update()
{
	result = system->update();
	ERRCHECK(result);
}
