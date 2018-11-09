#include "GameManager.h"

#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "ExpSystem.h"
#include "PlayerComponent.h"
#include "ExpComponent.h"
#include "StatsComponent.h"
#include "AnimationSystem.h"

GameManager::GameManager()
{
}

void GameManager::init()
{
	city_generator.generate(24, 24, entity_manager, multimedia_manager);

	auto& entity = entity_manager.create_entity();

	entity_manager.create_component<PlayerComponent>(entity);
	entity_manager.create_component<VelocityComponent>(entity);
	entity_manager.create_component<AnimationComponent>(entity);

	auto& position_component = entity_manager.create_component<PositionComponent>(entity, multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2);
	auto& d_component = entity_manager.create_component<DrawableComponent>(entity);
	
	const auto animated_texture = multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedTexture::AnimationDirection::vertical);
	d_component.texture = animated_texture;
	d_component.texture->set_position({ position_component.x, position_component.y });

	entity_manager.create_system<InputSystem>(input_manager);
	entity_manager.create_system<AnimationSystem>();
	entity_manager.create_system<DrawSystem>(multimedia_manager);
	entity_manager.create_system<MoveSystem>();
}

void GameManager::handle()
{
	entity_manager.update();
}
