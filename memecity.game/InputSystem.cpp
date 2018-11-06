#include "InputSystem.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"
#include "AnimationComponent.h"

std::string InputSystem::SYSTEM_TYPE = "InputSystem";

InputSystem::InputSystem(std::weak_ptr<InputManager> input_manager)
{
	this->input_manager = input_manager;
}

void InputSystem::run(EntityManager& em)
{
	auto entities = em.get_entities_with_component(PlayerComponent::COMPONENT_TYPE);

	for (auto entity : entities)
	{
		auto velocity_component = dynamic_cast<VelocityComponent*>(em.get_component_of_entity(entity->id, VelocityComponent::COMPONENT_TYPE));
		
		auto animation_component = dynamic_cast<AnimationComponent*>(em.get_component_of_entity(entity->id, AnimationComponent::COMPONENT_TYPE));
		
		if (this->input_manager.lock()->is_pressed(ATTACK))
		{
			animation_component->is_fighting = true;
		}
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

std::string InputSystem::get_type()
{
	return SYSTEM_TYPE;
}

void InputSystem::run(EntityManager& em, EventArgs& e)
{
}
