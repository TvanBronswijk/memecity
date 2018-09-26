#include "Graphics.h"

Graphics* Graphics::sInstance = nullptr;
bool Graphics::sInitialized = false;

Graphics* Graphics::Instance()
{
	if (sInstance == nullptr)
		sInstance = new Graphics();

	return sInstance;
}

void Graphics::Release()
{
	delete sInstance;
	sInstance = nullptr;

	sInitialized = false;
}

bool Graphics::Initialized()
{
	return sInitialized;
}


Graphics::Graphics()
{
	mBackBuffer = nullptr;
	sInitialized = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL initialization error: %s\n", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("MeMeCiTy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (mWindow == nullptr)
	{
		printf("Window creation error: %s\n", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (mRenderer == nullptr)
	{
		printf("Renderer creation error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);

	int flags = IMG_INIT_PNG;
	if (!(IMG_Init(flags) & flags))
	{
		printf("Image creation error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF initialization error: %s\n", TTF_GetError());
		return false;
	}

	mBackBuffer = SDL_GetWindowSurface(mWindow);
	return true;
}

SDL_Texture* Graphics::LoadTexture(std::string path)
{
	SDL_Texture* tex = nullptr;

	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == nullptr)
	{
		printf("Image load error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
		return tex;
	}

	tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (tex == nullptr)
	{
		printf("Create texture error: %s\n", IMG_GetError());
		return tex;
	}

	SDL_FreeSurface(surface);

	return tex;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (surface == nullptr)
	{
		printf("Text render error: %s\n", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (tex == nullptr)
	{
		printf("Text texture creation error: %s\n", SDL_GetError());
		return nullptr;
	}

	SDL_FreeSurface(surface);
	return tex;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend)
{
	SDL_RenderCopy(mRenderer, tex, clip, rend);
}

void Graphics::Render()
{
	SDL_RenderPresent(mRenderer);
}
