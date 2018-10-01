#include "AudioFacade.h"
#include "AssetManager.h"

AudioFacade::AudioFacade(std::shared_ptr<AssetManager> assetManager)
{
	asset_manager = assetManager;
}

void AudioFacade::Init() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Audio Initialization error: " << SDL_GetError() << std::endl;
	}
}

void Stopchunck(int channel) {
	Mix_HaltChannel(channel);
}

void AudioFacade::OpenAudio(int frequency, int channel, int chunksize) {
	if (Mix_OpenAudio(frequency, MIX_DEFAULT_FORMAT, channel, chunksize) < 0) {
		std::cout << "Audio error: " << Mix_GetError() << std::endl;
	}
}
int AudioFacade::PlaySound(const char* name, int repeats, int volume) {
	Mix_Chunk *sound = asset_manager->GetSFX(name); // smaller than 10 sec
	
	//it = chunks.find(name);
	//if (it != chunks.end()) {
	//	sound = &it->second;
	//}
	//else {
	//	sound = Mix_LoadWAV(name);
	//	if (!sound) {
	//		std::cout << "Audio recover error: " << Mix_GetError() << std::endl;
	//		return -1;
	//	}
	//}

	Mix_VolumeChunk(sound, volume);
	int channel = Mix_PlayChannel(-1, sound, repeats);
	//chunks.insert(std::pair<const char*, Mix_Chunk>(name, *sound));
	Mix_ChannelFinished(Stopchunck);
	sound = nullptr;
	return channel;
}

void AudioFacade::PlayBackgroundSound(const char* name, int volume) {
	//bgm = Mix_LoadMUS(name);
	//if (!bgm) {
	//	std::cout << "Audio recover error: " << Mix_GetError() << std::endl;
	//	return;
	//}

	Mix_VolumeMusic(volume);

	if (!Mix_PlayingMusic()) {
		Mix_PlayMusic(asset_manager->GetMusic(name), -1);
	}

}

void AudioFacade::PauseBackgroundSound() {
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

void AudioFacade::StopBackgroundSound() {
	//Stop the music 
	if (Mix_PlayingMusic) {
		Mix_HaltMusic();
		//Mix_FreeMusic(bgm);
		//bgm = nullptr;
	}
}

void AudioFacade::CloseAudio() {
	//for (it = chunks.begin(); it != chunks.end(); ++it)
	//	Mix_FreeChunk(&it->second);
	//dchunks.clear;
	Mix_Quit();
}