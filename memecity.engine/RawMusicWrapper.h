#ifndef _RAW_MUSIC_WRAPPER_H
#define _RAW_MUSIC_WRAPPER_H
#include <SDL_mixer.h>

class RawMusicWrapper
{
private:
	Mix_Music* music = nullptr;

public:
	RawMusicWrapper() = default;
	RawMusicWrapper(Mix_Music* music);
	~RawMusicWrapper();

	Mix_Music* operator->() const
	{
		return music;
	}
	Mix_Music* operator*() const
	{
		return music;
	}
};
#endif
