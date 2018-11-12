#ifndef _RAW_SURFACE_WRAPPER_H
#define _RAW_SURFACE_WRAPPER_H
#include <SDL.h>

class RawSurfaceWrapper
{
private:
	SDL_Surface* surface;

public:
	RawSurfaceWrapper()
		: surface(nullptr) {}

	RawSurfaceWrapper(SDL_Surface* sur)
		: surface(sur) {}

	~RawSurfaceWrapper()
	{
		SDL_FreeSurface(surface);
	}

	SDL_Surface* get() const
	{
		return surface;
	}
	SDL_Surface* operator->() const
	{
		return surface;
	}
	SDL_Surface* operator*()  const
	{
		return surface;
	}
};

#endif
