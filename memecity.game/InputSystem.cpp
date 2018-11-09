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
		auto velocity_component = em.get_component_of_entity<VelocityComponent>(entity.get(), VelocityComponent::COMPONENT_TYPE);


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
