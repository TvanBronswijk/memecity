#include "GameManager.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "PlayerComponent.h"

bool GameManager::init()
{
	
	if (multimedia_manager->init())
	{
		multimedia_manager->play_background_music("bgm.mp3", 50);

		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(50, 50, entity_manager, multimedia_manager);

		auto entity = entity_manager->create_entity();
		entity_manager->register_component(new PlayerComponent(entity));
		entity_manager->register_component(new VelocityComponent(entity));
		entity_manager->register_component(new PositionComponent(entity, 640.0f, 512.0f));

		auto d_component = new DrawableComponent(entity);
		d_component->texture = multimedia_manager->get_texture("red.bmp", 0, 0, 32, 32);
		d_component->texture->translate({ 640.0f, 512.0f });
		entity_manager->register_component(d_component);

		entity_manager->register_system(new InputSystem(input_manager));
		entity_manager->register_system(new DrawSystem(multimedia_manager));
		entity_manager->register_system(new MoveSystem());

		return true;
	}
	
	return false;
}

void GameManager::handle()
{
	timer->update();
	input_manager->update();
	entity_manager->update();
	if (timer->get_delta_time() >= 1.0f / 60)
	{
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

