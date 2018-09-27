#include "GraphicsFacade.h"

GraphicsFacade::GraphicsFacade() 
{
	this->screen_width = 640;
	this->screen_height = 480;
	Init();
}

GraphicsFacade* GraphicsFacade::GetInstance()
{
	if (instance == nullptr) {
		instance = new GraphicsFacade();
	}
	return instance;
}

bool GraphicsFacade::RenderTexture(const std::string& file)
{
	auto image_surface = SDL_LoadBMP(file.c_str());
	if (image_surface == nullptr)
	{
		printf("SDL load image error: %s\n", SDL_GetError());
		return false;
	}

	SDL_BlitSurface(image_surface, nullptr, window_surface, nullptr);
	SDL_UpdateWindowSurface(sdl_window);
	SDL_FreeSurface(image_surface);
	SDL_FreeSurface(window_surface);

	image_surface = nullptr;
	window_surface = nullptr;

	return true;
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

	sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
	if (sdl_renderer == nullptr)
	{
		printf("Renderer creation error: %s\n", SDL_GetError());
		return false;
	}

	window_surface = SDL_GetWindowSurface(sdl_window);
	return true;
}

