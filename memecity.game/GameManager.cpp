#include "GameManager.h"

#include "Generate\Strategy\BSP\BSP.h"
#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "ExpSystem.h"
#include "PlayerComponent.h"
#include "ExpComponent.h"
#include "StatsComponent.h"

GameManager::GameManager()
{
}

void GameManager::init()
{
	city_generator.set_strategy<generate::strategy::bsp::BSP>();
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
}

void GameManager::handle()
{
	entity_manager.update();
}
