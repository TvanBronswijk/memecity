#ifndef _GRAPHICSFACADE_H
#define _GRAPHICSFACADE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <SDL_image.h>

class GraphicsFacade
{
	private:
		SDL_Window* sdl_window{};
		SDL_Surface* window_surface{};
		SDL_Renderer* sdl_renderer{};

	public:
		GraphicsFacade();
		bool Init();

		int screen_width;
		int screen_height;
		bool isInitialized;

		SDL_Texture* LoadTexture(std::string file) const;
		SDL_Texture* LoadTextTexture(TTF_Font* font, std::string text, SDL_Color color) const;
		void DrawTexture(SDL_Texture* texture, SDL_Rect* clipped_rect, SDL_Rect* render_rect) const;		
		void Render() const;
		void Clear() const;
};

#endif
