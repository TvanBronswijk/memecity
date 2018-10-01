#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "Texture.h"
#include "GraphicsFacade.h"
#include <thread>

int main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: IS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto graphicsFacade = GraphicsFacade::GetInstance();
	auto texture = new Texture("BlikBier.bmp");
	bool quit = false;

	while (!quit) 
	{
		SDL_Event events;

		while (SDL_PollEvent(&events) != 0)
		{
			if (events.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		texture->Translate({ 2.0f, 2.0f });
	//	texture->Update();
		graphicsFacade->Clear();
		texture->Render();
		graphicsFacade->Render();
	}

	GraphicsFacade::Release();
	AssetManager::Release();
	delete texture;
	return 0;
}
