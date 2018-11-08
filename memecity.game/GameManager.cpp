#include "GameManager.h"

GameManager::GameManager()
{
	city_generator = std::make_unique<CityGenerator>();
	entity_manager = std::make_unique<EntityManager>();
}

void GameManager::init()
{
	city_generator->generate(50, 50, entity_manager, multimedia_manager);

	auto entity = entity_manager->create_entity();
	entity_manager->register_component(new PlayerComponent(entity));
	entity_manager->register_component(new VelocityComponent(entity));
	auto position_component = new PositionComponent(entity, multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2);
	entity_manager->register_component(position_component);

		auto d_component = new DrawableComponent(entity);

		animated_character = multimedia_manager->get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		d_component->texture = animated_character;
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
}

void GameManager::handle()
{
	entity_manager->update();
}
