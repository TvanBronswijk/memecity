#include "GameManager.h"
#include "ColliderSystem.h"

#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "ExpSystem.h"
#include "PlayerComponent.h"
#include "ExpComponent.h"
#include "StatsComponent.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"

void GameManager::init()
{
	city_generator.generate(50, 50, entity_manager, multimedia_manager);

	auto texture = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
	texture->set_position({ (float)multimedia_manager.get_screen_width() / 2, (float)multimedia_manager.get_screen_height() / 2 });
	ecs::builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<PlayerComponent>()
		.with_component<PositionComponent>(multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2)
		.with_component<VelocityComponent>()
		.with_component<ColliderComponent>(64.0f, 64.0f);
		.with_component<DrawableComponent>(texture);

	entity_manager.create_system<DrawSystem>(ecs::System::draw);
	entity_manager.create_system<InputSystem>(ecs::System::update, input_manager);
	entity_manager.create_system<MoveSystem>();
	auto& collider_system = entiy_manager.create_system<ColliderSystem>();
	collider_system.collider_event.bind([&](ecs::EntityManager& em, ColliderEventArgs args) { move_system.on_collision(em, args); });
}

void GameManager::update(float dt)
{
	entity_manager.update(ecs::System::update);
}

void GameManager::draw() 
{
	entity_manager.update(ecs::System::draw);
}
