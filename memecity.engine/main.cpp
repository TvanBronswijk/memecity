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

	const auto multimediaManager = std::make_shared<MultimediaManager>(false);

	if (multimediaManager->init())
	{
		multimediaManager->play_background_music("bgm.mp3", 50);
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
				multimediaManager->clear_graphics();
				texture->Render();
				multimediaManager->render_graphics();
				timer->Reset();

				if (inputFacade.IsPressed(ESCAPE))
				{
					multimediaManager->pause_background_music();
				}

				if (inputFacade.IsPressed(UP))
				{
					multimediaManager->play_sound_effect("biem.mp3", 0, 50, 1);
				}

				if (inputFacade.IsPressed(DOWN))
				{
					multimediaManager->play_sound_effect("biem.mp3", 0, 50, 2);
				}
			}
		}

		return 0;
	}

	return -1;
}
