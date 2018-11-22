#include "GraphicsFacade.h"
#include <SDL_image.h>
#include "..\Exceptions.h"
#include "Wrappers\RawTextureWrapper.h"
#include "Wrappers\RawFontWrapper.h"

namespace memecity::engine::sdl {
	using namespace exceptions;
	GraphicsFacade::GraphicsFacade(bool is_fullscreen) : is_initialized(false)
	{
		this->is_fullscreen = is_fullscreen;
		screen_height = 600;
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

	std::unique_ptr<RawTextureWrapper> GraphicsFacade::load_text_texture(RawFontWrapper& font, std::string text, const SDL_Color &color) const
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

		std::unique_ptr<SDL_Rect> sdl_clipped_rect;
		if (clipped_rect != nullptr) {
			sdl_clipped_rect = std::make_unique<SDL_Rect>();
			sdl_clipped_rect->x = clipped_rect->x;
			sdl_clipped_rect->y = clipped_rect->y;
			sdl_clipped_rect->w = clipped_rect->w;
			sdl_clipped_rect->h = clipped_rect->h;
		}
		std::unique_ptr<SDL_Rect> sdl_render_rect = std::make_unique<SDL_Rect>();
		sdl_render_rect->x = render_rect.x;
		sdl_render_rect->y = render_rect.y;
		sdl_render_rect->w = render_rect.w;
		sdl_render_rect->h = render_rect.h;


		if (render_rect.x > -viewport_offset && render_rect.x < screen_width + viewport_offset &&
			render_rect.y > -viewport_offset && render_rect.y < screen_height + viewport_offset) {
			SDL_RenderCopy(sdl_renderer->get(), *texture, sdl_clipped_rect.get(), sdl_render_rect.get());
		}
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

	void GraphicsFacade::render() const
	{
		SDL_RenderPresent(sdl_renderer->get());
	}
}
