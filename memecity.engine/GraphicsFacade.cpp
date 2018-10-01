#include "GraphicsFacade.h"

GraphicsFacade::GraphicsFacade()
{
	
}


bool GraphicsFacade::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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

	if (SDL_SetWindowFullscreen(sdl_window, SDL_WINDOW_FULLSCREEN_DESKTOP) != 0)
	{
		printf("Window FullScreen error: %s\n", SDL_GetError());
		return false;
	}

	SDL_GetWindowSize(sdl_window, &screen_width, &screen_height);

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == nullptr)
	{
		printf("Renderer creation error: %s\n", SDL_GetError());
		return false;
	}

	window_surface = SDL_GetWindowSurface(sdl_window);
	return true;
}

SDL_Texture* GraphicsFacade::LoadTexture(const std::string path) const
{
	SDL_Texture* texture = nullptr;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		printf("Image load error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
		return texture;
	}

	texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
	if (texture == nullptr)
	{
		printf("Create texture error: %s\n", IMG_GetError());
		return texture;
	}

	SDL_FreeSurface(surface);
	return texture;
}

SDL_Texture* GraphicsFacade::LoadTextTexture(TTF_Font* font, std::string text, const SDL_Color color) const
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
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
	return tex;
}

void GraphicsFacade::DrawTexture(SDL_Texture* texture, SDL_Rect* clipped_rect, SDL_Rect* render_rect) const
{
	SDL_RenderCopy(sdl_renderer, texture, clipped_rect, render_rect);
}

void GraphicsFacade::Clear() const
{
	SDL_RenderClear(sdl_renderer);
}

void GraphicsFacade::Render() const
{
	SDL_RenderPresent(sdl_renderer);
}



