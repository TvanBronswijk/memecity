#include "GameManager.h"
#include "../memecity.engine.ecs/Entity.h"
#include "ExpComponent.h"
#include "ExpSystem.h"
#include "StatsComponent.h"


bool GameManager::init()
{
	
	if (multimedia_manager->init())
	{
		multimedia_manager->play_background_music("bgm.mp3", 50);
		texture = multimedia_manager->get_texture("BlikBier.bmp");
		text = multimedia_manager->get_text_texture("Test", "Blazed.ttf", 50, { 255,10,10 });
		text->translate({ 100.0f, 100.0f });

		Entity* player = em.create_entity();
		ExpComponent* player_exp_component = new ExpComponent(player);
		StatsComponent* player_stats_component = new StatsComponent(player);
		ExpSystem* player_exp_system = new ExpSystem();
		em.register_component(player_exp_component);
		em.register_system(player_exp_system);
		em.register_component(player_stats_component);

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

