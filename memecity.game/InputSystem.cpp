#include "InputSystem.h"

using namespace ecs;

system_typetoken InputSystem::SYSTEM_TYPE = "InputSystem";

InputSystem::InputSystem(InputManager &input_manager) : input_manager(input_manager)
{
}

void InputSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component(PlayerComponent::COMPONENT_TYPE);

	for (auto entity : entities)
	{

		auto velocity_component =
			dynamic_cast<VelocityComponent*>(em.get_component_of_entity(entity->id, VelocityComponent::COMPONENT_TYPE));
		
		auto animation_component = dynamic_cast<AnimationComponent*>(em.get_component_of_entity(entity->id, AnimationComponent::COMPONENT_TYPE));

		if (this->input_manager.is_pressed(ATTACK))
		{
			animation_component->is_fighting = true;
		}
		if (this->input_manager.is_pressed(UP))
		{
			velocity_component->y += 5;
		}
		if (this->input_manager.is_pressed(DOWN))
		{
			velocity_component->y -= 5;
		}
		if (this->input_manager.is_pressed(LEFT))
		{
			velocity_component->x -= 5;
		}
		if (this->input_manager.is_pressed(RIGHT))
		{
			velocity_component->x += 5;
		}
	}
}
