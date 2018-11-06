#include "InputSystem.h"

using namespace ecs;

system_typetoken InputSystem::SYSTEM_TYPE = "InputSystem";

InputSystem::InputSystem(std::weak_ptr<InputManager> input_manager)
{
	this->input_manager = input_manager;
}

void InputSystem::run(EntityManager& em)
{
	auto entities = em.get_entities_with_component(PlayerComponent::COMPONENT_TYPE);

	for (auto entity : entities)
	{
		auto velocity_component = em.get_component_of_entity<VelocityComponent>(entity.get(), VelocityComponent::COMPONENT_TYPE);


		if (this->input_manager.lock()->is_pressed(UP))
		{
			velocity_component->y += 5;
		}
		if (this->input_manager.lock()->is_pressed(DOWN))
		{
			velocity_component->y -= 5;
		}
		if (this->input_manager.lock()->is_pressed(LEFT))
		{
			velocity_component->x -= 5;
		}
		if (this->input_manager.lock()->is_pressed(RIGHT))
		{
			velocity_component->x += 5;
		}
	}
}
