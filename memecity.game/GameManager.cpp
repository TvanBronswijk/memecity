#include "GameManager.h"

bool GameManager::init()
{
	
	if (multimedia_manager->init())
	{
		multimedia_manager->play_background_music("bgm.mp3", 50);

		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(64, 64, entity_manager, multimedia_manager);
		entity_manager->register_system(new DrawSystem(multimedia_manager));
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

		entity_manager->update();
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

