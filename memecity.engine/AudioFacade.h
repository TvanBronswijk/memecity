#ifndef _AUDIOFACADE_H
#define _AUDIOFACADE_H

#include<SDL_mixer.h>
#include <SDL.h>
#include <iostream>

class AudioFacade
{
public:
	///<summary>Initializes the SDL Audio.</summary>
	bool init() const;

	///<summary>Open the SDL audio mixer with a given audio format.</summary>
	void open_audio(int frequency,const int channels,const int chunksize) const;

	///<summary>Play a sound effect with a given amount of repeats, volume and the selected channel.</summary>
	void play_sound_effect(Mix_Chunk* sound,const int repeats,const int volume,const int channel = 0) const;

	///<summary>Checks if audio is playing on the given channel.</summary>
	bool is_playing(const int channel) const;

	///<summary>Play a given background music with a specified volume.</summary>
	void play_background_music(Mix_Music* music,const int volume) const;

	///<summary>If the music is paused, resume. Otherwise pause.</summary>
	void pause_background_music() const;

	///<summary>If background music is playing, stop it.</summary>
	void stop_background_music() const;

	///<summary>Cleanup audio</summary>
	void close_audio() const;
};

#endif