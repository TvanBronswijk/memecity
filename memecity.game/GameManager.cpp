#include "GameManager.h"



bool GameManager::init()
{
	city_generator = std::make_unique<CityGenerator>();
	auto em = std::make_unique<EntityManager>();
	city_generator->generate(64, 64, em);
	if (multimedia_manager->init())
	{
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
		multimedia_manager->clear_graphics();
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

