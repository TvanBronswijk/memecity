#ifndef _RAW_MUSIC_WRAPPER_H
#define _RAW_MUSIC_WRAPPER_H
#include <SDL_mixer.h>

namespace memecity::engine::sdl {
	class RawMusicWrapper
	{
	private:
		Mix_Music* music;

	public:
		RawMusicWrapper()
			: music(nullptr) {};

		RawMusicWrapper(Mix_Music* music)
			: music(music) {};

		~RawMusicWrapper()
		{
			Mix_FreeMusic(music);
		}

		Mix_Music* get() const
		{
			return music;
		}
		Mix_Music* operator->() const
		{
			return music;
		}
		Mix_Music* operator*() const
		{
			return music;
		}
	};
}
#endif
