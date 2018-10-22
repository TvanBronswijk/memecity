#include "GameManager.h"



bool GameManager::init()
{
	if (multimedia_manager->init())
	{
		multimedia_manager->play_background_music("bgm.mp3", 50);
		texture = multimedia_manager->get_texture("BlikBier.bmp");
		text = multimedia_manager->get_text_texture("Test", "Blazed.ttf", 50, { 255,10,10 });
		text->translate({ 100.0f, 100.0f });
		return true;
	}
	return false;
}


void GameManager::handle()
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

