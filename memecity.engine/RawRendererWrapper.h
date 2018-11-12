#ifndef _RAW_RENDERER_WRAPPER_H
#define _RAW_RENDERER_WRAPPER_H
#include <SDL.h>

class RawRendererWrapper
{
private:
	SDL_Renderer* renderer;

public:
	RawRendererWrapper()
		: renderer(nullptr) {}

	RawRendererWrapper(SDL_Renderer* ren)
		: renderer(ren) {}

	~RawRendererWrapper()
	{
		SDL_DestroyRenderer(renderer);
	}

	SDL_Renderer* get() const
	{
		return renderer;
	}
	SDL_Renderer* operator->() const
	{
		return renderer;
	}
	SDL_Renderer* operator*()  const
	{
		return renderer;
	}
};

#endif
