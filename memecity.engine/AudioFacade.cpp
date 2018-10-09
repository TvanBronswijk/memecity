#include "AudioFacade.h"

bool AudioFacade::init() const
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Audio Initialization error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void AudioFacade::open_audio(const int frequency, const int channel, const int chunksize) const
{
	if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channel, chunksize) < 0) 
	{
		std::cout << "Audio error: " << Mix_GetError() << std::endl;
	}
}

void AudioFacade::play_sound_effect(Mix_Chunk* sound, const int repeats, const int volume, const int channel) const
{
	if (!is_playing(channel))
	{
		Mix_VolumeChunk(sound, volume);
		Mix_PlayChannel(channel, sound, repeats);
	}
}

bool AudioFacade::is_playing(int const channel) const
{
	return Mix_Playing(channel) == 1;
}

void AudioFacade::play_background_music(Mix_Music* music, const int volume) const
{

	Mix_VolumeMusic(volume);

	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, -1);
	}

}

void AudioFacade::pause_background_music() const
{
	//If the music is paused 
	if (Mix_PausedMusic() == 1)
	{ //Resume the music 
		Mix_ResumeMusic();
	} //If the music is playing 
	else
	{ //Pause the music 
		Mix_PauseMusic();
	}
}

void AudioFacade::stop_background_music() const
{
	//Stop the music 
	if (Mix_PlayingMusic) 
	{
		Mix_HaltMusic();
	}
}

void AudioFacade::close_audio() const
{
	Mix_Quit();
}

