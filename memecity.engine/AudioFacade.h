#ifndef _AUDIOFACADE_H
#define _AUDIOFACADE_H

#include<SDL_mixer.h>
#include <SDL.h>
#include <iostream>

class AudioFacade
{

	public:

		bool Init();
		void OpenAudio(int frequency, int channel, int chunksize);
		void PlaySoundEffect(Mix_Chunk* sound, int repeats, int volume, int channel = 0) const;
		bool IsPlaying(int channel) const;
		void PlayBackgroundMusic(Mix_Music* music, int volume) const;
		void PauseBackgroundMusic() const;
		void StopBackgroundMusic() const;
		void CloseAudio() const;
};

#endif