#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "Texture.h"
#include "GraphicsFacade.h"
#include <thread>
#include "TimerFacade.h"
#include "InputFacade.h"
#include "AudioFacade.h"

int main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: IS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto graphicsFacade = std::make_shared<GraphicsFacade>();

	if (graphicsFacade->Init()) {
		auto assetManager = std::make_shared<AssetManager>(graphicsFacade);
		auto texture = std::make_unique<Texture>(assetManager, graphicsFacade, "BlikBier.bmp");
		auto timer = std::make_unique<TimerFacade>();
		auto inputFacade = InputFacade();
		auto audioFacade = std::make_shared<AudioFacade>(assetManager);
		audioFacade->Init();
		audioFacade->PlayBackgroundSound("bgm.mp3", 50);

		while (!inputFacade.GetQuitPressed())
		{
			timer->Update();

			inputFacade.Update();

			if (timer->DeltaTime() >= 1.0f / 60) {

				texture->Translate(Vector2(120.0f, 120.0f) * timer->DeltaTime());
				//	texture->Update();
				graphicsFacade->Clear();
				texture->Render();
				graphicsFacade->Render();
				timer->Reset();
				if (inputFacade.IsPressed(ESCAPE))
				{
					audioFacade->PauseBackgroundSound();
				}
			}
		}

		return 0;
	}
	return -1;
}
