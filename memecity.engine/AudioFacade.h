#ifndef _AUDIOFACADE_H
#define _AUDIOFACADE_H

#include<SDL.h>
#include<SDL_mixer.h>
#include <iostream>
#include <map>

class AudioFacade
{
public:
	void Init();

	void OpenAudio(int frequency, int channel, int chunksize);

	int PlaySound(const char* name, int repeats, int volume);

	void PlayBackgroundSound(const char* name, int volume);

	void PauzeBackgroundSound();

	void StopBackgroundSound();

	void CloseAudio();
};

#endif