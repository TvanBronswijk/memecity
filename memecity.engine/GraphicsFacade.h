#ifndef _GRAPHICSFACADE_H
#define _GRAPHICSFACADE_H

#include <SDL.h>
#include "Texture.h"

class GraphicsFacade
{
	private:
		GraphicsFacade();
		bool Init();

		int screen_width;
		int screen_height;

		static GraphicsFacade* instance;

		SDL_Window* sdl_window{};
		SDL_Surface* window_surface{};
		SDL_Renderer* sdl_renderer{};

	public:
		static GraphicsFacade* GetInstance();
		bool RenderTexture(const std::string& file);
};

#endif
