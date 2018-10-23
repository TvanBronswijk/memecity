#include "MoveSystem.h"

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

void MoveSystem::run(EntityManager &em, EventArgs e)
{
}

bool MoveSystem::is_on_event(Event * e)
{
	return false;
}

std::string MoveSystem::get_type()
{
	return SYSTEM_TYPE;
}
