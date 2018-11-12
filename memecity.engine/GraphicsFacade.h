#ifndef _GRAPHICSFACADE_H
#define _GRAPHICSFACADE_H

#include <SDL.h>
#include <string>
#include "RectangleFacade.h"

class RawFontWrapper;
class RawTextureWrapper;

class GraphicsFacade
{
private:
	bool is_fullscreen;
	SDL_Window* sdl_window{};
	SDL_Surface* window_surface{};
	SDL_Renderer* sdl_renderer{};

public:
	///<summary>Constructor with the default setting to disable fullscreen.</summary>
	GraphicsFacade(bool is_fullscreen);

	///<summary>Initializes the SDL Video and enables fullscreen if selected.</summary>
	bool init();

	int screen_width;
	int screen_height;
	bool is_initialized;

	///<summary>Loads texture from path into memory.</summary>
	std::unique_ptr<RawTextureWrapper> load_texture(std::string file) const;

	///<summary>Loads a text texture from path into memory.</summary>
	std::unique_ptr<RawTextureWrapper> load_text_texture(RawFontWrapper& font, std::string text, const SDL_Color &color) const;
	
	///<summary>Loads a texture into the buffer of the SDL_Renderer object.</summary>
	void draw_texture(const RawTextureWrapper& texture, const RectangleFacade* clipped_rect, const RectangleFacade* render_rect) const;

	///<summary>Renders the SDL_Renderer buffer.</summary>
	void render() const;
	
	///<summary>Clears the SDL_Renderer buffer.</summary>
	void clear() const;
};

#endif