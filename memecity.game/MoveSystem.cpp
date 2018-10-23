﻿#include "MoveSystem.h"

std::string MoveSystem::SYSTEM_TYPE = "MoveSystem";

void MoveSystem::run(EntityManager& em)
{
	auto components = em.get_components_of_type(VelocityComponent::COMPONENT_TYPE);

	for (auto velocity_component : components)
	{
		auto current_position =
			dynamic_cast<PositionComponent*>(em.get_component_of_entity(velocity_component->entity_id, PositionComponent::COMPONENT_TYPE));
		const auto current_velocity_component = dynamic_cast<VelocityComponent*>(velocity_component);

		if (current_velocity_component->x != 0)
		{
			current_position->x += current_velocity_component->x;
			current_position->diffx = current_velocity_component->x;
			current_velocity_component->x = 0;
		}
		else
		{
			current_position->diffx = 0;
		}

		if (current_velocity_component->y != 0)
		{
			current_position->y += current_velocity_component->y;
			current_position->diffy = current_velocity_component->y;
			current_velocity_component->y = 0;
		}
		else
		{
			current_position->diffy = 0;
		}
	}
}

void MoveSystem::run(EntityManager& em, const EventArgs& e)
{
	const auto collider_event_args = dynamic_cast<const ColliderEventArgs*>(&e);
	if (collider_event_args != nullptr)
	{
		auto components = em.get_components_of_type(VelocityComponent::COMPONENT_TYPE);

		for (auto velocity_component : components)
		{
			const auto current_position =
				dynamic_cast<PositionComponent*>(em.get_component_of_entity(velocity_component->entity_id, PositionComponent::COMPONENT_TYPE));

			if (velocity_component->entity_id == collider_event_args->source_entity_id)
			{
				current_position->x = -1;
				current_position->y = -1;
			}
		}
	}
}


std::string MoveSystem::get_type()
{
	return SYSTEM_TYPE;
}
