#include "RawTextureWrapper.h"

RawTextureWrapper::RawTextureWrapper(SDL_Texture* tex) 
{
	texture = tex;
}

RawTextureWrapper::~RawTextureWrapper()
{
	//SDL_DestroyTexture(texture);
}
