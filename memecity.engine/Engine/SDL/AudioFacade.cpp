#include "AudioFacade.h"
#include "Wrappers\RawMusicWrapper.h"
#include "..\Exceptions.h"
#include <iostream>
#include <SDL.h>
#include "Wrappers\RawSfxWrapper.h"

namespace memecity::engine::sdl {
	using namespace exceptions;

	bool AudioFacade::init() const
	{
		if (SDL_Init(SDL_INIT_AUDIO) < 0) {
			throw SDLException(Level::error, Mix_GetError());
		}

		return true;
	}

	void AudioFacade::open_audio(int frequency, int channels, int chunksize) const
	{
		/*if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) < 0)
		{
			throw SDLException(Level::error, Mix_GetError());
		}*/
	}

	void AudioFacade::play_sound_effect(const RawSfxWrapper& sound, int repeats, int volume, int channel) const
	{
		if (!is_playing(channel))
		{
			Mix_VolumeChunk(*sound, volume);
			Mix_PlayChannel(channel, *sound, repeats);
		}
	}

	bool AudioFacade::is_playing(int channel) const
	{
		return Mix_Playing(channel) == 1;
	}

	void AudioFacade::play_background_music(const RawMusicWrapper& music, int volume) const
	{

		Mix_VolumeMusic(volume);

		if (!Mix_PlayingMusic()) {
			Mix_PlayMusic(*music, -1);
		}

	}

	void AudioFacade::pause_background_music() const
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}

	void AudioFacade::stop_background_music() const
	{
		if (Mix_PlayingMusic())
		{
			Mix_HaltMusic();
		}
	}

	void AudioFacade::close_audio() const
	{
		Mix_Quit();
	}
}
