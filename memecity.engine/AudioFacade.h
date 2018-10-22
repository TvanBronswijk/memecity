#ifndef _AUDIOFACADE_H
#define _AUDIOFACADE_H

#include<SDL_mixer.h>
#include <SDL.h>
#include <iostream>

class AudioFacade
{
public:
	bool init() const;
	void open_audio(int frequency, int channels, int chunksize) const;
	void play_sound_effect(Mix_Chunk* sound, int repeats, int volume, int channel = 0) const;
	bool is_playing(int channel) const;
	void play_background_music(Mix_Music* music, int volume) const;
	void pause_background_music() const;
	void stop_background_music() const;
	void close_audio() const;
};

#endif