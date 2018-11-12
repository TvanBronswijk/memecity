#include "RawSfxWrapper.h"

RawSfxWrapper::RawSfxWrapper(Mix_Chunk* sfx)
{
	this->sfx = sfx;
}

RawSfxWrapper::~RawSfxWrapper()
{
	Mix_FreeChunk(sfx);
}
