#include "GraphicsFacade.h"
#include "RawTextureWrapper.h"
#include <SDL_image.h>
#include "RawFontWrapper.h"

GraphicsFacade::GraphicsFacade(bool is_fullscreen): is_initialized(false)
{
	this->is_fullscreen = is_fullscreen;
	screen_height = 600;
	screen_width = 1280;
}

bool GraphicsFacade::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL initialization error: %s\n", SDL_GetError());
		return false;
	}

	sdl_window = SDL_CreateWindow("MemeCity", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	if (sdl_window == nullptr)
	{
		printf("Window creation error: %s\n", SDL_GetError());
		return false;
	}

	if (is_fullscreen)
	{
		if (SDL_SetWindowFullscreen(sdl_window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
		{
			printf("Window FullScreen error: %s\n", SDL_GetError());
			return false;
		}	
	}

	SDL_GetWindowSize(sdl_window, &screen_width, &screen_height);

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == nullptr)
	{
		printf("Renderer creation error: %s\n", SDL_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF initialization error: %s\n", TTF_GetError());
		return false;
	}

	window_surface = SDL_GetWindowSurface(sdl_window);
	return true;
}

std::unique_ptr<RawTextureWrapper> GraphicsFacade::load_texture(const std::string path) const
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		printf("Image load error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
		return std::make_unique<RawTextureWrapper>(texture);
	}

	texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
	if (texture == nullptr)
	{
		printf("Create texture error: %s\n", IMG_GetError());
		return std::make_unique<RawTextureWrapper>(texture);
	}

	SDL_FreeSurface(surface);
	return std::make_unique<RawTextureWrapper>(texture);
}

std::unique_ptr<RawTextureWrapper> GraphicsFacade::load_text_texture(RawFontWrapper& font, std::string text, const SDL_Color &color) const
{
	SDL_Surface* surface = TTF_RenderText_Solid(*font, text.c_str(), color);
	if (surface == nullptr)
	{
		printf("Text render error: %s\n", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(sdl_renderer, surface);
	if (tex == nullptr)
	{
		printf("Text texture creation error: %s\n", SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(surface);
	return std::make_unique<RawTextureWrapper>(tex);
}

void GraphicsFacade::draw_texture(const RawTextureWrapper& texture, const Rectangle* clipped_rect, const Rectangle* render_rect) const
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
	sdl_render_rect->x = render_rect->x;
	sdl_render_rect->y = render_rect->y;
	sdl_render_rect->w = render_rect->w;
	sdl_render_rect->h = render_rect->h;


	if (render_rect->x > -viewport_offset && render_rect->x < screen_width + viewport_offset &&
		render_rect->y > -viewport_offset && render_rect->y < screen_height + viewport_offset) {
		SDL_RenderCopy(sdl_renderer, *texture, sdl_clipped_rect.get(), sdl_render_rect.get());
	}
}

void GraphicsFacade::clear() const
{
	SDL_RenderClear(sdl_renderer);
}

void GraphicsFacade::render() const
{
	SDL_RenderPresent(sdl_renderer);
}