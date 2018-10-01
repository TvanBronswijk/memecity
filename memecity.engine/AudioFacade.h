#ifndef _AUDIOFACADE_H
#define _AUDIOFACADE_H

#include<SDL.h>
#include<SDL_mixer.h>
#include <iostream>
#include <map>
#include "AssetManager.h"

class AudioFacade
{

private:
	std::shared_ptr<AssetManager> asset_manager;
public:

	AudioFacade(std::shared_ptr<AssetManager> assetManager);

	void Init();

	void OpenAudio(int frequency, int channel, int chunksize);

	int PlaySound(const char* name, int repeats, int volume);

	void PlayBackgroundSound(const char* name, int volume);

	void PauseBackgroundSound();

	void StopBackgroundSound();

	void CloseAudio();
};

#endif