#include "GraphicsFacade.h"
#include <SDL_image.h>
#include "..\Exceptions.h"
#include "Wrappers\RawTextureWrapper.h"
#include "Wrappers\RawFontWrapper.h"

namespace memecity::engine::sdl {
	using namespace exceptions;

	SDL_Rect to_sdl_rect(const Rectangle& rect) {
		SDL_Rect result_rect;
		result_rect.x = std::round(rect.x);
		result_rect.y = std::round(rect.y);
		result_rect.w = std::round(rect.w);
		result_rect.h = std::round(rect.h);
		return result_rect;
	}

	GraphicsFacade::GraphicsFacade(bool is_fullscreen) : is_initialized(false)
	{
		this->is_fullscreen = is_fullscreen;
		screen_height = 640;
		screen_width = 1280;		
	}

	bool GraphicsFacade::init()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			throw SDLException(Level::error, SDL_GetError());
		}

		sdl_window = std::make_unique<RawWindowWrapper>(SDL_CreateWindow("MemeCity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN));
		if (sdl_window == nullptr)
		{
			throw SDLException(Level::error, SDL_GetError());
		}

		if (is_fullscreen)
		{
			if (SDL_SetWindowFullscreen(sdl_window->get(), SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
			{
				throw SDLException(Level::error, SDL_GetError());
			}
		}

		SDL_GetWindowSize(sdl_window->get(), &screen_width, &screen_height);

		sdl_renderer = std::make_unique<RawRendererWrapper>(SDL_CreateRenderer(sdl_window->get(), -1, SDL_RENDERER_ACCELERATED));
		if (sdl_renderer == nullptr)
		{
			throw SDLException(Level::error, SDL_GetError());
		}

		if (TTF_Init() == -1)
		{
			throw SDLException(Level::error, SDL_GetError());
		}

		if (SDL_SetRenderDrawBlendMode(sdl_renderer->get(), SDL_BLENDMODE_BLEND) != 0)
		{
			
		}

		window_surface = std::make_unique<RawSurfaceWrapper>(SDL_GetWindowSurface(sdl_window->get()));
		return true;
	}

	std::unique_ptr<RawTextureWrapper> GraphicsFacade::load_texture(const std::string path) const
	{
		std::unique_ptr<RawTextureWrapper> texture;
		std::unique_ptr<RawSurfaceWrapper> surface = std::make_unique<RawSurfaceWrapper>(IMG_Load(path.c_str()));
		if (surface->get() == nullptr)
		{
			throw SDLException(Level::error, IMG_GetError());
		}
		texture = std::make_unique<RawTextureWrapper>(SDL_CreateTextureFromSurface(sdl_renderer->get(), surface->get()));
		if (texture->get() == nullptr)
		{
			throw SDLException(Level::error, IMG_GetError());
		}
		return texture;
	}

	std::unique_ptr<RawFontWrapper> GraphicsFacade::load_font(std::string path, int size) const
	{
		std::unique_ptr<RawFontWrapper> font = std::make_unique<sdl::RawFontWrapper>(TTF_OpenFont(path.c_str(), size));
		if (font == nullptr) {
			throw SDLException(Level::error, SDL_GetError());
		}
		return font;
	}

	std::unique_ptr<RawTextureWrapper> GraphicsFacade::load_text_texture(const RawFontWrapper& font, std::string text, const SDL_Color color) const
	{
		std::unique_ptr<RawSurfaceWrapper> surface = std::make_unique<RawSurfaceWrapper>(TTF_RenderText_Solid(*font, text.c_str(), color));

		if (surface->get() == nullptr)
		{
			throw SDLException(Level::error, IMG_GetError());
		}
		std::unique_ptr<RawTextureWrapper> texture = std::make_unique<RawTextureWrapper>(SDL_CreateTextureFromSurface(sdl_renderer->get(), surface->get()));
		if (texture->get() == nullptr)
		{
			throw SDLException(Level::error, IMG_GetError());
		}

		return texture;
	}

	void GraphicsFacade::draw_texture(const RawTextureWrapper& texture, const Rectangle& render_rect, const Rectangle* clipped_rect) const
	{

		if (render_rect.x > -viewport_offset && render_rect.x < screen_width + viewport_offset &&
			render_rect.y > -viewport_offset && render_rect.y < screen_height + viewport_offset) {
			SDL_Rect sdl_render_rect = to_sdl_rect(render_rect);
			SDL_Rect sdl_clipped_rect;
			if (clipped_rect != nullptr) {
				sdl_clipped_rect = to_sdl_rect(*clipped_rect);
			}
			SDL_RenderCopy(sdl_renderer->get(), *texture, clipped_rect == nullptr ? nullptr : &sdl_clipped_rect, &sdl_render_rect);
		}
	}

	void GraphicsFacade::draw_rectangle(const Rectangle& rect, bool fill, SDL_Color color)
	{
		SDL_SetRenderDrawColor(sdl_renderer->get(), color.r, color.g, color.b, color.a);
		SDL_Rect sdl_rect = to_sdl_rect(rect);
		if (fill) {
			SDL_RenderFillRect(sdl_renderer->get(), &sdl_rect);
		}
		else {
			SDL_RenderDrawRect(sdl_renderer->get(), &sdl_rect);
		}
		SDL_SetRenderDrawColor(sdl_renderer->get(), 0, 0, 0, 255);
	}

	void GraphicsFacade::get_dimensions(const RawTextureWrapper & texture, int & width, int & height)
	{
		SDL_QueryTexture(*texture, nullptr, nullptr, &width, &height);
	}

	void GraphicsFacade::clear() const
	{
		SDL_RenderClear(sdl_renderer->get());
	}

	void GraphicsFacade::set_fullscreen(bool fullscreen_enabled)
	{
		is_fullscreen = fullscreen_enabled;

		if (is_fullscreen)
		{
			if (SDL_SetWindowFullscreen(sdl_window->get(), SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
			{
				throw SDLException(Level::error, SDL_GetError());
			}
		}
		else
		{
			if (SDL_SetWindowFullscreen(sdl_window->get(), 0) != 0)
			{
				throw SDLException(Level::error, SDL_GetError());
			}
		}
		SDL_GetWindowSize(sdl_window->get(), &screen_width, &screen_height);
	}

	bool GraphicsFacade::get_fullscreen() const
	{
		return is_fullscreen;
	}

	void GraphicsFacade::render() const
	{
		SDL_RenderPresent(sdl_renderer->get());
	}
}
