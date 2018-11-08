#include "GameManager.h"
#include "ColliderSystem.h"

GameManager::GameManager()
{
}

void GameManager::init()
{
	city_generator.generate(16, 16, entity_manager, multimedia_manager);
	auto& entity = entity_manager.create_entity();
	entity_manager.create_component<PlayerComponent>(entity);
	entity_manager.create_component<VelocityComponent>(entity);
	entity_manager.create_component<ColliderComponent>(entity, 64.0f, 64.0f);
	auto& position_component = entity_manager.create_component<PositionComponent>(entity, multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2);
	auto& d_component = entity_manager.create_component<DrawableComponent>(entity);
	auto animated_character = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
	d_component.texture = animated_character;
	d_component.texture->set_position({ position_component.x, position_component.y });
	
	entity_manager.create_system<InputSystem>(input_manager);
	entity_manager.create_system<DrawSystem>(multimedia_manager);
	auto& move_system = entity_manager.create_system<MoveSystem>();
	auto& collider_system = entity_manager.create_system<ColliderSystem>();
	collider_system.collider_event.bind([&](ecs::EntityManager& em, ColliderEventArgs args) { move_system.on_collision(em, args); });
}

void GameManager::handle()
{
	entity_manager.update();
}
