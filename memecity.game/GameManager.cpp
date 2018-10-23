#include "GameManager.h"
#include "../memecity.engine.ecs/Entity.h"
#include "ExpComponent.h"
#include "ExpSystem.h"
#include "StatsComponent.h"


bool GameManager::init()
{
	if (multimedia_manager->init())
	{
		

		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(64, 64, entity_manager, multimedia_manager);

		// Test to show an example how to create a animated character
		animated_character = multimedia_manager->get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		animated_character->set_position(Vector2(200.0, 200.0));

		const auto animated_character_entity = entity_manager->create_entity();
		const auto draw_system = new DrawSystem(multimedia_manager);
		const auto drawable_component = new DrawableComponent(animated_character_entity);
		entity_manager->register_component(drawable_component);
		entity_manager->register_system(draw_system);
		drawable_component->texture = animated_character;

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
		animated_character->update();

		if (input_manager->is_pressed(ESCAPE))
		{
			multimedia_manager->pause_background_music();
		}

		if (input_manager->is_pressed(LEFT))
		{
			animated_character->set_walking_direction(AnimatedCharacter::left);
			animated_character->translate(Vector2(-60.0f, 0.0f) * timer->get_delta_time());
		}

		if (input_manager->is_pressed(RIGHT))
		{
			animated_character->set_walking_direction(AnimatedCharacter::right);
			animated_character->translate(Vector2(+60.0f, 0.0f) * timer->get_delta_time());
		}

		if (input_manager->is_pressed(UP))
		{
			animated_character->set_walking_direction(AnimatedCharacter::up);
			animated_character->translate(Vector2(0.0f, -60.0f) * timer->get_delta_time());
		}

		if (input_manager->is_pressed(DOWN))
		{
			animated_character->set_walking_direction(AnimatedCharacter::down);
			animated_character->translate(Vector2(0.0f, +60.0f) * timer->get_delta_time());
		}

		timer->reset();
	}
}

