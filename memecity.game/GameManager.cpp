#include "GameManager.h"
#include "../memecity.engine.ecs/Entity.h"
#include "ExpComponent.h"
#include "ExpSystem.h"
#include "StatsComponent.h"
#include "ColliderEvent.h"
#include "ColliderSystem.h"
#include "MoveSystem.h"


bool GameManager::init()
{

	if (multimedia_manager->init())
	{
		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(64, 64, entity_manager, multimedia_manager);
		entity_manager->register_system(new DrawSystem(multimedia_manager));
		//auto collider_event = new ColliderEvent();
		//const auto collider_system = new ColliderSystem(collider_event);
		const auto move_system = new MoveSystem();
		//entity_manager->register_system(collider_system);
		entity_manager->register_system(move_system);
		//collider_event->subscribe(move_system);
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

