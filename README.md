# FMOD Wrapper Library Project

### Andrea Ricci - University of Verona - Computer Game Development Master
### Sound Programming course

## Description

Wrapper library for the FMOD Core API.
The solution is composed by two projects:
- SoundLibrary: Wrapper static library that uses the FMOD Core API.
- SoundClient: Console project that shows what the library can do using a simple user interface.

## Functionalities

- Play three different audio files, some using static loading and others streaming
- One file is set to loop, the others are set to one-shot
- Change volume & pan
- Pause & stop
- In the user interface you can see the track progress, the state of the channel (paused/playing) and the number of active channels.

## Instructions

### Build

This projects requires the FMOD Core API installed in the default path:

C:\Program Files (x86)\FMOD SoundSystem\FMOD Studio API Windows\api\core

Compile it using SoundClient as Startup Project.

### Pre-compiled executable

The pre-compiled executable can be found in the attached "Build.zip" compressed folder.