#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "Texture.h"
#include <thread>
#include "TimerFacade.h"
#include "MultimediaManager.h"
#include "InputManager.h"

int main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: ITS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	const auto multimediaManager = std::make_shared<MultimediaManager>(false);
	const auto inputManager = std::make_unique<InputManager>();

	if (multimediaManager->Init())
	{
		multimediaManager->PlayBackgroundMusic("bgm.mp3", 50);
		auto texture = std::make_unique<Texture>(multimediaManager, "BlikBier.bmp");
		auto timer = std::make_unique<TimerFacade>();

		while (!inputManager->IsQuitPressed())
		{
			timer->Update();
			if (timer->DeltaTime() >= 1.0f / 60)
			{
				inputManager->Update();

				texture->Translate(Vector2(120.0f, 120.0f) * timer->DeltaTime());
				multimediaManager->ClearGraphics();
				texture->Render();
				multimediaManager->RenderGraphics();
				timer->Reset();

				if (inputManager->IsPressed(ESCAPE))
				{
					multimediaManager->PauseBackgroundMusic();
				}

				if (inputManager->IsPressed(UP))
				{
					multimediaManager->PlaySoundEffect("biem.mp3", 0, 50, 1);
				}

				if (inputManager->IsPressed(DOWN))
				{
					multimediaManager->PlaySoundEffect("biem.mp3", 0, 50, 2);
				}
			}
		}

		return 0;
	}

	return -1;
}
