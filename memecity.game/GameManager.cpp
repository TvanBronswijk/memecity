#include "GameManager.h"

bool GameManager::init()
{
	if (multimedia_manager.init())
	{
		city_generator = std::make_unique<CityGenerator>();
		entity_manager = std::make_unique<EntityManager>();
		city_generator->generate(50, 50, entity_manager, multimedia_manager);

		auto entity = entity_manager->create_entity();
		entity_manager->register_component(new PlayerComponent(entity));
		entity_manager->register_component(new VelocityComponent(entity));
		auto position_component = new PositionComponent(entity, multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2);
		entity_manager->register_component(position_component);

		auto d_component = new DrawableComponent(entity);
		d_component->texture = multimedia_manager.get_texture("red.bmp", 0, 0, 32, 32);
		d_component->texture->set_position({ position_component->x, position_component->y });
		entity_manager->register_component(d_component);

		entity_manager->register_system(new InputSystem(input_manager));
		entity_manager->register_system(new DrawSystem(multimedia_manager));
		entity_manager->register_system(new MoveSystem());

		// Test to show an example how to create a animated character
		animated_character = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		animated_character->set_position(Vector2(200.0, 200.0));

		const auto animated_character_entity = entity_manager->create_entity();
		const auto drawable_component = new DrawableComponent(animated_character_entity);
		entity_manager->register_component(drawable_component);
		drawable_component->texture = animated_character;

		return true;
	}

	return false;
}

void GameManager::handle()
{
	animated_character->update();
	entity_manager->update();
	if (input_manager.is_pressed(ESCAPE))
	{
		multimedia_manager.pause_background_music();
	}

	if (input_manager.is_pressed(LEFT))
	{
		animated_character->set_walking_direction(AnimatedCharacter::left);
		animated_character->translate(Vector2(-60.0f, 0.0f) * timer->get_delta_time());
	}

	if (input_manager.is_pressed(RIGHT))
	{
		animated_character->set_walking_direction(AnimatedCharacter::right);
		animated_character->translate(Vector2(+60.0f, 0.0f) * timer->get_delta_time());
	}

	if (input_manager.is_pressed(UP))
	{
		animated_character->set_walking_direction(AnimatedCharacter::up);
		animated_character->translate(Vector2(0.0f, -60.0f) * timer->get_delta_time());
	}

	if (input_manager.is_pressed(DOWN))
	{
		animated_character->set_walking_direction(AnimatedCharacter::down);
		animated_character->translate(Vector2(0.0f, +60.0f) * timer->get_delta_time());
	}

}

