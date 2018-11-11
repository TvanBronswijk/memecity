#ifndef _RAW_TEXTURE_WRAPPER_H
#define _RAW_TEXTURE_WRAPPER_H
#include <SDL.h>

class RawTextureWrapper
{
private:
	SDL_Texture* texture = nullptr;

public:
	RawTextureWrapper() = default;
	RawTextureWrapper(SDL_Texture* tex);
	~RawTextureWrapper();

	SDL_Texture* operator->() const
	{
		return texture;
	}
	SDL_Texture* operator*()  const
	{
		return texture;
	}
};

#endif

