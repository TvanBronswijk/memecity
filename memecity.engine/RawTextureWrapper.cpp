#include "RawTextureWrapper.h"

RawTextureWrapper::RawTextureWrapper(SDL_Texture* tex) 
{
	this->texture = tex;
}

RawTextureWrapper::~RawTextureWrapper()
{
	//SDL_DestroyTexture(texture);
}
