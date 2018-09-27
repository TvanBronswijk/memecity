#ifndef _GRAPHICSFACADE_H
#define _GRAPHICSFACADE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>

class GraphicsFacade
{
	private:
		GraphicsFacade();
		bool Init();

		static GraphicsFacade* instance;

		SDL_Window* sdl_window{};
		SDL_Surface* window_surface{};
		SDL_Renderer* sdl_renderer{};

	public:
		int screen_width;
		int screen_height;
		bool isInitialized;

		static GraphicsFacade* GetInstance();
		SDL_Texture* LoadTexture(std::string file);
		SDL_Texture* LoadTextTexture(TTF_Font* font, std::string text, SDL_Color color);
		void DrawTexture(SDL_Texture* texture, SDL_Rect* clipped_rect, SDL_Rect* render_rect);		
		void Render();
		void Clear();
		static void Release();
};

#endif
