#include "AudioFacade.h"

bool AudioFacade::Init() 
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Audio Initialization error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

void AudioFacade::OpenAudio(int frequency, int channel, int chunksize) 
{
	if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channel, chunksize) < 0) 
	{
		std::cout << "Audio error: " << Mix_GetError() << std::endl;
	}
}

void AudioFacade::PlaySoundEffect(Mix_Chunk* sound, int repeats, int volume, int channel) const
{
	if (!IsPlaying(channel))
	{
		Mix_VolumeChunk(sound, volume);
		Mix_PlayChannel(channel, sound, repeats);
		sound = nullptr;
	}
}

bool AudioFacade::IsPlaying(int channel) const
{
	return Mix_Playing(channel) == 1;
}

void AudioFacade::PlayBackgroundMusic(Mix_Music* music, int volume) const
{

	Mix_VolumeMusic(volume);

	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(music, -1);
	}

}

void AudioFacade::PauseBackgroundMusic() const
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

void AudioFacade::StopBackgroundMusic() const
{
	//Stop the music 
	if (Mix_PlayingMusic) 
	{
		Mix_HaltMusic();
	}
}

void AudioFacade::CloseAudio() const
{
	Mix_Quit();
}

