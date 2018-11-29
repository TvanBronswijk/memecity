#include "AudioFacade.h"
#include "Wrappers\RawMusicWrapper.h"
#include "Wrappers\RawSfxWrapper.h"
#include "..\Exceptions.h"
#include <iostream>
#include <SDL.h>

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
		if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) < 0)
		{
			throw SDLException(Level::error, Mix_GetError());
		}
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

	std::unique_ptr<RawMusicWrapper> AudioFacade::load_music(std::string path) const
	{
		std::unique_ptr<RawMusicWrapper> music = std::make_unique<sdl::RawMusicWrapper>(Mix_LoadMUS(path.c_str()));
		if (music == nullptr) {
			throw SDLException(Level::error, Mix_GetError());
		}
		return music;
	}

	std::unique_ptr<RawSfxWrapper> AudioFacade::load_sfx(std::string path) const
	{
		std::unique_ptr<RawSfxWrapper> sfx = std::make_unique<sdl::RawSfxWrapper>(Mix_LoadWAV(path.c_str()));
		if (sfx == nullptr) {
			throw SDLException(Level::error, Mix_GetError());
		}
		return sfx;
	}

	void AudioFacade::close_audio() const
	{
		Mix_Quit();
	}
}
