#ifndef _RAW_SFX_WRAPPER_H
#define _RAW_SFX_WRAPPER_H
#include <SDL_mixer.h>

class RawSfxWrapper
{
private:
	Mix_Chunk* sfx;
public:
	RawSfxWrapper()
		:sfx(nullptr) {}

	RawSfxWrapper(Mix_Chunk* sfx) 
	: sfx(sfx) {}

	~RawSfxWrapper()
	{
		Mix_FreeChunk(sfx);
	}

	Mix_Chunk* operator->() const
	{
		return sfx;
	}
	Mix_Chunk* operator*() const
	{
		return sfx;
	}
};
#endif
