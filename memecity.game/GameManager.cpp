#include "GameManager.h"

using namespace ecs;

bool GameManager::init()
{
	if (multimedia_manager->init())
	{
		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(32, 32, entity_manager, multimedia_manager);

		auto entity = entity_manager->create_entity();
		entity_manager->create_component<PlayerComponent>(entity);
		entity_manager->create_component<VelocityComponent>(entity);
		auto& position_component = entity_manager->create_component<PositionComponent>(entity, multimedia_manager->get_screen_width() / 2, multimedia_manager->get_screen_height() / 2);

		auto& d_component = entity_manager->create_component<DrawableComponent>(entity);

		animated_character = multimedia_manager->get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		d_component.texture = animated_character;
		d_component.texture->set_position({ position_component.x, position_component.y });


		entity_manager->create_system<InputSystem>(input_manager);
		entity_manager->create_system<DrawSystem>(multimedia_manager);
		entity_manager->create_system<MoveSystem>();

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
		if (input_manager->is_pressed(ESCAPE))
		{
			multimedia_manager->pause_background_music();
		}
		timer->reset();
	}
}

