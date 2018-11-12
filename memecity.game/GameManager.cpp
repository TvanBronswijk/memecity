#include "GameManager.h"
#include "Generate\Strategy\BSP\BSP.h"
#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "PlayerComponent.h"
#include "AnimationSystem.h"
#include "DrawableComponent.h"
#include "Color.h"
#include "TextTexture.h"

GameManager::GameManager() = default;


void GameManager::init()
{
	city_generator.set_strategy<generate::strategy::bsp::BSP>();
	city_generator.generate(50, 50, entity_manager, multimedia_manager);
	auto& entity = entity_manager.create_entity();

	entity_manager.create_component<PlayerComponent>(entity);
	entity_manager.create_component<VelocityComponent>(entity);
	entity_manager.create_component<AnimationComponent>(entity);

	auto& position_component = entity_manager.create_component<PositionComponent>(entity, multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2);
	auto& d_component = entity_manager.create_component<DrawableComponent>(entity);

	d_component.texture = multimedia_manager.get_animated_texture(*timer, "SpriteSheet.png", 0, 0, 48, 48, 4, 0.25f, AnimatedTexture::AnimationDirection::vertical);
	d_component.texture->set_position({ position_component.x, position_component.y });


	auto& text_entity = entity_manager.create_entity();
	auto& text_d_component = entity_manager.create_component<DrawableComponent>(text_entity);
	text_d_component.texture = multimedia_manager.get_text_texture("Health: 500", "Minecraftia-Regular.ttf", 16, { 255,255,255 });
	text_d_component.texture->set_parent(d_component.texture.get());
	text_d_component.texture->set_position({ 0, -30 });
	entity_manager.create_system<InputSystem>(input_manager);
	entity_manager.create_system<AnimationSystem>();
	entity_manager.create_system<DrawSystem>(multimedia_manager);
	entity_manager.create_system<MoveSystem>();
}

void GameManager::handle()
{
	entity_manager.update();
}
