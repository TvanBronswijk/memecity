#ifndef _GRAPHICSFACADE_H
#define _GRAPHICSFACADE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <SDL_image.h>

class GraphicsFacade
{
private:
	bool is_fullscreen;
	SDL_Window* sdl_window{};
	SDL_Surface* window_surface{};
	SDL_Renderer* sdl_renderer{};

public:
	GraphicsFacade(bool is_fullscreen);
	bool init();

	int screen_width;
	int screen_height;
	bool is_initialized;

	SDL_Texture* load_texture(std::string file) const;
	SDL_Texture* load_text_texture(TTF_Font* font, std::string text, const SDL_Color &color) const;
	void draw_texture(SDL_Texture* texture, SDL_Rect* clipped_rect, SDL_Rect* render_rect) const;		
	void render() const;
	void clear() const;
};

#endif
