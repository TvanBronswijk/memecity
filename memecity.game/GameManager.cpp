#include "GameManager.h"

#include "Generate\Strategy\BSP\BSP.h"
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
	city_generator.set_strategy<generate::strategy::bsp::BSP>();
	city_generator.generate(50, 50, entity_manager, multimedia_manager);

	auto& entity = ecs::builder::EntityBuilder(entity_manager)
		.add_component<PlayerComponent>()
		.add_component<PositionComponent>(multimedia_manager.get_screen_width() / 2, multimedia_manager.get_screen_height() / 2)
		.add_component<VelocityComponent>()
		.build();

	entity_manager.create_component<DrawableComponent>(
			entity, 
			multimedia_manager.get_animated_texture(timer.get(), "SpriteSheet.png", 0, 0, 48, 48, 4, 0.5f, AnimatedCharacter::vertical)
			).texture->set_position({ (float)multimedia_manager.get_screen_width() / 2, (float)multimedia_manager.get_screen_height() / 2 });

	entity_manager.create_system<DrawSystem>(ecs::System::draw);
	entity_manager.create_system<InputSystem>(ecs::System::update, input_manager);
	entity_manager.create_system<MoveSystem>();
}

void GameManager::update(float dt)
{
	entity_manager.update(ecs::System::update);
}

void GameManager::draw() 
{
	entity_manager.update(ecs::System::draw);
}
