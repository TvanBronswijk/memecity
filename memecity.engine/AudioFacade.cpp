#include "AudioFacade.h"

bool AudioFacade::init() const
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Audio Initialization error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void AudioFacade::open_audio(int frequency, int channels, int chunksize) const
{
	if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channels, chunksize) < 0) 
	{
		std::cout << "Audio error: " << Mix_GetError() << std::endl;
	}
}

void AudioFacade::play_sound_effect(Mix_Chunk* sound, int repeats, int volume, int channel) const
{
	if (!is_playing(channel))
	{
		Mix_VolumeChunk(sound, volume);
		Mix_PlayChannel(channel, sound, repeats);
	}
}

bool AudioFacade::is_playing(int channel) const
{
	return Mix_Playing(channel) == 1;
}

void AudioFacade::play_background_music(Mix_Music* music, int volume) const
{

	Mix_VolumeMusic(volume);

	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, -1);
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
	if (Mix_PlayingMusic) 
	{
		Mix_HaltMusic();
	}
}

void AudioFacade::close_audio() const
{
	Mix_Quit();
}