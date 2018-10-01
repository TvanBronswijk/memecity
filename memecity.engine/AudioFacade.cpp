#include "AudioFacade.h"
#include "AssetManager.h"

AudioFacade::AudioFacade(std::shared_ptr<AssetManager> assetManager)
{
	asset_manager = assetManager;
}

void AudioFacade::Init() 
{
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Audio Initialization error: " << SDL_GetError() << std::endl;
	}
}

void Stopchunck(int channel) 
{
	Mix_HaltChannel(channel);
}

void AudioFacade::OpenAudio(int frequency, int channel, int chunksize) 
{
	if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channel, chunksize) < 0) 
	{
		std::cout << "Audio error: " << Mix_GetError() << std::endl;
	}
}
int AudioFacade::PlaySound(const char* name, int repeats, int volume, int channel) 
{
		if (IsPlaying(channel))
		{
			return -1;
		}

		Mix_Chunk *sound = asset_manager->GetSFX(name); // smaller than 10 sec

		Mix_VolumeChunk(sound, volume);
		int channelIndex = Mix_PlayChannel(channel, sound, repeats);
		//Mix_ChannelFinished(Stopchunck);
		sound = nullptr;
		return channelIndex;

}

bool AudioFacade::IsPlaying(int channel)
{
	return Mix_Playing(channel) == 1;
}


void AudioFacade::PlayBackgroundSound(const char* name, int volume) 
{

	Mix_VolumeMusic(volume);

	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(asset_manager->GetMusic(name), -1);
	}

}

void AudioFacade::PauseBackgroundSound() 
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

void AudioFacade::StopBackgroundSound() 
{
	//Stop the music 
	if (Mix_PlayingMusic) {
		Mix_HaltMusic();
	}
}

void AudioFacade::CloseAudio() 
{
	Mix_Quit();
}

