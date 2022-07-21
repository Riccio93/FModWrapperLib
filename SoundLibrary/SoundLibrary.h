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
	using ChannelGroup = FMOD::ChannelGroup*;

	//Functions ------------------------------------------------------------------------

	//Initializes the system
	void Initialize(int MaxChannels);

	//Loads an audio file
	Sound Load(const char* fileName, LoadMode loadMode = LoadMode::LOAD_DEFAULT);

	//Plays an audio file on the selected channel (looping depending on soundMode, ONE_SHOT or LOOP)
	void Play(Sound sound, Channel* channel, SoundMode soundMode);

	//Stops the audio file on the selected channel
	void Stop(Channel channel);

	//Toggles pause on and off on the selected channel
	void TogglePause(Channel channel);

	//Stops the audio files
	void StopAll(ChannelGroup channelGroup);

	//Toggles pause on and off
	void TogglePauseAll(ChannelGroup channelGroup);

	//Sets the volume (0 mute, 1 max volume)
	void SetVolume(Channel channel, float volume);

	//Sets the volume to the master group (0 mute, 1 max volume)
	void SetVolumeAll(ChannelGroup channelGroup, float volume);

	//Sets the pan (-1 left, 0 center, 1 right)
	void SetPan(Channel channel, float pan);

	//Sets the pan to the master group (-1 left, 0 center, 1 right)
	void SetPanAll(ChannelGroup channelGroup, float pan);

	//Returns if the selected channel is playing something
	bool IsPlaying(Channel channel);

	//Returns if the selected channel is paused
	bool IsPaused(Channel channel);

	//Returns if the master group is paused
	bool IsGroupPaused(ChannelGroup channelGroup);

	//Gets milliseconds from the start of the audio file
	unsigned int GetMilliseconds(Channel channel);

	//Gets total audio file length in milliseconds
	unsigned int GetTotalLength(Sound sound);

	//Returns the sound currently playing on the selected channel
	Sound GetCurrentlyPlayingSound(Channel channel);

	//Returns the number of the currently active channels
	int GetPlayingChannels();

	//Returns the master channel group
	SoundLibrary::ChannelGroup GetMasterChannelGroup();

	//Calls the built-in system.Update
	void Update();

	//Variables ------------------------------------------------------------------------

	FMOD::System* system;
};