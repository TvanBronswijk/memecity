#include "GameManager.h"

#include "../memecity.engine.ecs/Entity.h"
#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "PlayerComponent.h"
#include "ExpComponent.h"
#include "ExpSystem.h"
#include "StatsComponent.h"
#include "AISystem.h"
#include "MoveSystem.h"
#include "FightingSystem.h"
#include "InteractionComponent.h"
#include "InteractionSystem.h"

GameManager::GameManager()
{
}

void GameManager::init()
{
	city_generator.generate(50, 50, entity_manager, multimedia_manager);
	auto& entity = entity_manager.create_entity();
	entity_manager.create_component<PlayerComponent>(entity);
	entity_manager.create_component<VelocityComponent>(entity);
	auto& position_component = entity_manager.create_component<PositionComponent>(entity, multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2);
	auto& d_component = entity_manager.create_component<DrawableComponent>(entity);
	auto animated_character = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
	d_component.texture = animated_character;
	d_component.texture->set_position({ position_component.x, position_component.y });

	entity_manager.create_system<InputSystem>(input_manager);
	entity_manager.create_system<DrawSystem>(multimedia_manager);
	entity_manager.create_system<MoveSystem>();
	//test to show an example  for a NPC
	entity_manager.create_system<FightingSystem>();
	entity_manager.create_system<AISystem>();
	entity_manager.create_system<InteractionSystem>(multimedia_manager);

	for (size_t i = 0; i < 1; i++) {
		auto& npc = entity_manager.create_entity();
		entity_manager.create_component<AIComponent>(npc);
		entity_manager.create_component<VelocityComponent>(npc);
		entity_manager.create_component<LevelComponent>(npc, 1);
		entity_manager.create_component<HealthComponent>(npc, 100);
		entity_manager.create_component<StatsComponent>(npc);
		entity_manager.create_component<InteractionComponent>(npc);
		auto& d_component_npc = entity_manager.create_component<DrawableComponent>(npc);
		auto& npc_position = entity_manager.create_component<PositionComponent>(npc, 10 * i, 10 * i);
		auto animated_npc = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical);
		d_component_npc.texture = animated_npc;
		d_component_npc.texture->set_position({ npc_position.x , npc_position.y + (multimedia_manager.get_screen_height() - (npc_position.y * 2)) });
	}
	// end test	

	// events
	auto& input_system = entity_manager.create_system<InputSystem>(input_manager);
	//input_system.attack_event.bind(ExpSystem::on_exp_gain);

}

void GameManager::handle()
{
	entity_manager.update();
}
