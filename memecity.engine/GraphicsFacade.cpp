#include "GraphicsFacade.h"

///<summary>Constructor with the default setting to disable fullscreen.</summary>
GraphicsFacade::GraphicsFacade(bool is_fullscreen): is_initialized(false)
{
	this->is_fullscreen = is_fullscreen;
	screen_height = 480;
	screen_width = 640;
}

///<summary>Initializes the SDL Video and enables fullscreen if selected.</summary>
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

///<summary>Loads texture from path into memory.</summary>
SDL_Texture* GraphicsFacade::load_texture(const std::string path) const
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

///<summary>Loads a text texture from path into memory.</summary>
SDL_Texture* GraphicsFacade::load_text_texture(TTF_Font* font, std::string text, const SDL_Color &color) const
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

///<summary>Loads a texture into the buffer of the SDL_Renderer object.</summary>
void GraphicsFacade::draw_texture(SDL_Texture* texture, SDL_Rect* clipped_rect, SDL_Rect* render_rect) const
{
	SDL_RenderCopy(sdl_renderer, texture, clipped_rect, render_rect);
}

///<summary>Clears the SDL_Renderer buffer.</summary>
void GraphicsFacade::clear() const
{
	SDL_RenderClear(sdl_renderer);
}


///<summary>Renders the SDL_Renderer buffer.</summary>
void GraphicsFacade::render() const
{
	SDL_RenderPresent(sdl_renderer);
}