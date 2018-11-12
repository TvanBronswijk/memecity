#include "InputSystem.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"
#include "AnimationComponent.h"

using namespace ecs;

void InputSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component<PlayerComponent>();

	for (auto entity : entities)
	{

		auto velocity_component = entity.get().get<VelocityComponent>();
			
		auto animation_component = entity.get().get<AnimationComponent>();

		if (this->input_manager.is_pressed(Attack))
		{
			animation_component->is_fighting = true;
		}
		if (this->input_manager.is_pressed(Up))
		{
			velocity_component->y += 5;
		}
		if (this->input_manager.is_pressed(Down))
		{
			velocity_component->y -= 5;
		}
		if (this->input_manager.is_pressed(Left))
		{
			velocity_component->x -= 5;
		}
		if (this->input_manager.is_pressed(Right))
		{
			velocity_component->x += 5;
		}
	}
}
