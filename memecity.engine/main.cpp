#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#include "Texture.h"
#include <thread>
#include "TimerFacade.h"
#include "InputFacade.h"
#include "MultimediaManager.h"

int main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: ITS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	const auto multimediaManager = std::make_shared<MultimediaManager>();

	if (multimediaManager->Init()) 
	{
		multimediaManager->PlayBackgroundMusic("bgm.mp3");
		auto texture = std::make_unique<Texture>(multimediaManager, "BlikBier.bmp");
		auto timer = std::make_unique<TimerFacade>();		
		auto inputFacade = InputFacade();

		while (!inputFacade.GetQuitPressed())
		{
			timer->Update();
			if (timer->DeltaTime() >= 1.0f / 60) 
			{
				inputFacade.Update();

				texture->Translate(Vector2(120.0f, 120.0f) * timer->DeltaTime());
				multimediaManager->ClearGraphics();
				texture->Render();
				multimediaManager->RenderGraphics();
				timer->Reset();

				if (inputFacade.IsPressed(ESCAPE))
				{
					multimediaManager->PauseBackgroundMusic();
				}

				if (inputFacade.IsPressed(UP))
				{
					multimediaManager->PlaySoundEffect("biem.mp3", 0, 50, 1);
				}

				if (inputFacade.IsPressed(DOWN))
				{
					multimediaManager->PlaySoundEffect("biem.mp3", 0, 50, 2);
				}
			}
		}

		return 0;
	}

	return -1;
}
