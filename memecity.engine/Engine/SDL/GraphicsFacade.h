#ifndef _GRAPHICSFACADE_H
#define _GRAPHICSFACADE_H
#include <SDL.h>
#include "..\Util\Rectangle.h"
#include "Wrappers\RawWindowWrapper.h"
#include "Wrappers\RawSurfaceWrapper.h"
#include "Wrappers\RawRendererWrapper.h"
#include <string>

namespace memecity::engine::sdl {
	class RawFontWrapper;
	class RawTextureWrapper;

	class GraphicsFacade
	{
	private:
		bool is_fullscreen;
		std::unique_ptr<RawWindowWrapper> sdl_window{};
		std::unique_ptr<RawSurfaceWrapper> window_surface{};
		std::unique_ptr<RawRendererWrapper> sdl_renderer{};
		static const int viewport_offset = 90;
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

		///<summary>Loads a surface into the buffer of the SDL_Renderer object.</summary>
		void draw_texture(const RawTextureWrapper& texture, const Rectangle& render_rect, const Rectangle* clipped_rect) const;

		///<summary>Renders the SDL_Renderer buffer.</summary>
		void render() const;

		///<summary>Clears the SDL_Renderer buffer.</summary>
		void clear() const;

		void set_fullscreen(bool fullscreen_enabled);
	};
}

#endif
