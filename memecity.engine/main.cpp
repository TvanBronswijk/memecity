#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "Texture.h"
#include "GraphicsFacade.h"
#include <thread>
#include "TimerFacade.h"

int main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: IS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto graphicsFacade = GraphicsFacade::GetInstance();
	auto timerFacade = TimerFacade::GetInstance();
	auto texture = new Texture("BlikBier.bmp");
	bool quit = false;

	while (!quit) 
	{
		SDL_Event events;
		timerFacade->Update();

		while (SDL_PollEvent(&events) != 0)
		{
			if (events.type == SDL_QUIT)
			{
				quit = true;
			}
		}
		if (timerFacade->DeltaTime() >= 1.0f / 120) {

			texture->Translate(Vector2( 50.0f, 50.0f ) * timerFacade->DeltaTime());
			//	texture->Update();
			graphicsFacade->Clear();
			texture->Render();
			graphicsFacade->Render();
			timerFacade->Reset();
		}
	}

	GraphicsFacade::Release();
	AssetManager::Release();
	TimerFacade::Release();
	delete texture;
	return 0;
}
