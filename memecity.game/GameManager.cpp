#include "GameManager.h"
#include "ColliderSystem.h"

#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "PlayerComponent.h"
#include "ExpComponent.h"
#include "ExpSystem.h"
#include "StatsComponent.h"
#include "AIComponent.h"
#include "HealthComponent.h"
#include "LevelComponent.h"
#include "AISystem.h"
#include "MoveSystem.h"
#include "FightingSystem.h"
#include "InteractionComponent.h"
#include "InteractionSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"
#include "DrawableComponent.h"

void GameManager::init()
{
	city_generator.generate(50, 50, entity_manager, multimedia_manager);

	auto texture = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
	texture->set_position({ static_cast<float>(multimedia_manager.get_screen_width()) / 2, static_cast<float>(multimedia_manager.get_screen_height()) / 2 });
	ecs::builder::EntityBuilder(entity_manager)
		.create_entity()
		.with_component<PlayerComponent>()
		//.with_component<ColliderComponent>(64.0f, 64.0f)
		.with_component<PositionComponent>(multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2)
		.with_component<VelocityComponent>()
		.with_component<DrawableComponent>(texture);

	entity_manager.create_system<DrawSystem>(ecs::System::draw);
	auto& input_system = entity_manager.create_system<InputSystem>(ecs::System::update, input_manager);
	entity_manager.create_system<MoveSystem>();
	//test to show an example  for a NPC
	auto& fighting_system = entity_manager.create_system<FightingSystem>();
	entity_manager.create_system<AISystem>();
	auto& interaciton_system = entity_manager.create_system<InteractionSystem>();

	for (size_t i = 0; i < 1; i++) {
		float x = 10 * i;
		float y = 10 * i;

		auto texture = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		texture->set_position({ x , y + (multimedia_manager.get_screen_height() - (y * 2)) });

		ecs::builder::EntityBuilder(entity_manager)
			.create_entity()
			.with_component<AIComponent>()
			.with_component<VelocityComponent>()
			.with_component<LevelComponent>()
			.with_component<HealthComponent>(100)
			.with_component<StatsComponent>()
			.with_component<InteractionComponent>()
			.with_component<DrawableComponent>(texture)
			.with_component<PositionComponent>(x, y)
			.with_component<InteractionComponent>();

	}
	// end test	

	// events
	input_system.interaction_event.bind([&](ecs::EntityManager& em, InteractionEventArgs args) { interaciton_system.on_interact(em, args); });
	input_system.attack_event.bind([&](ecs::EntityManager& em, AttackEventArgs args) { fighting_system.on_attack(em, args); });
}

void GameManager::update(float dt)
{
	entity_manager.update(ecs::System::update);
}

void GameManager::draw()
{
	entity_manager.update(ecs::System::draw);
}
