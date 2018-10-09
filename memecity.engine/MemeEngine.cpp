#include "MemeEngine.h"


int MemeEngine::main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: ITS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	const auto multimedia_manager = std::make_shared<MultimediaManager>(false);
	const auto input_manager = std::make_unique<InputManager>();

	if (multimedia_manager->init())
	{
		multimedia_manager->play_background_music("bgm.mp3", 50);
		auto texture = multimedia_manager->get_texture("BlikBier.bmp");
		auto text = multimedia_manager->get_text_texture("Test", "Blazed.ttf", 50, { 255,10,10 });
		text->translate({ 100.0f, 100.0f });
		auto timer = std::make_unique<TimerFacade>();

		while (!input_manager->is_quit_pressed())
		{
			timer->update();
			if (timer->get_delta_time() >= 1.0f / 60)
			{
				input_manager->update();

				texture->translate(Vector2(120.0f, 120.0f) * timer->get_delta_time());
				multimedia_manager->clear_graphics();
				texture->render();
				text->render();
				multimedia_manager->render_graphics();
				timer->reset();

				if (input_manager->is_pressed(ESCAPE))
				{
					multimedia_manager->pause_background_music();
				}

				if (input_manager->is_pressed(UP))
				{
					multimedia_manager->play_sound_effect("biem.mp3", 0, 50, 1);
				}

				if (input_manager->is_pressed(DOWN))
				{
					multimedia_manager->play_sound_effect("biem.mp3", 0, 50, 2);
				}
			}
		}

		return 0;
	}

	return -1;
}
