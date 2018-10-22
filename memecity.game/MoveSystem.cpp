#include "MoveSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"

std::string MoveSystem::SYSTEM_TYPE = "MoveSystem";

void MoveSystem::run(EntityManager& em)
{
	auto components = em.get_components_of_type(VelocityComponent::COMPONENT_TYPE);

	for (auto velocity_component : components)
	{
		auto current_position =
			dynamic_cast<PositionComponent*>(em.get_component_of_entity(velocity_component->entity_id, PositionComponent::COMPONENT_TYPE));
		const auto current_velocity_component = dynamic_cast<VelocityComponent*>(velocity_component);

		current_position->x += current_velocity_component->x;
		current_position->y += current_velocity_component->y;
	}
}

void MoveSystem::run(EntityManager & em, Event * e)
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
