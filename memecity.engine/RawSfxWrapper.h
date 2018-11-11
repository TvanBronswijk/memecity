#ifndef _RAW_SFX_WRAPPER_H
#define _RAW_SFX_WRAPPER_H
#include <SDL_mixer.h>

class RawSfxWrapper
{
private:
	Mix_Chunk* sfx = nullptr;
public:
	RawSfxWrapper() = default;
	RawSfxWrapper(Mix_Chunk* sfx);
	~RawSfxWrapper();

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
