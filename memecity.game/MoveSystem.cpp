#include "MoveSystem.h"
#include "VelocityComponent.h"
#include "PositionComponent.h"

void MoveSystem::run(EntityManager& em)
{
	auto components = em.get_components_of_type(VelocityComponent::COMPONENT_TYPE);

	for (auto velocity_component : components)
	{
		PositionComponent* current_position = 
			dynamic_cast<PositionComponent*>(em.get_component_of_entity(velocity_component->entity_id, PositionComponent::COMPONENT_TYPE));
		VelocityComponent* current_velocity_component = dynamic_cast<VelocityComponent*>(velocity_component);

		if (current_position->x > 0)
		{
			current_position->x += current_velocity_component->x;
		} else if (current_position->x < 0)
		{
			current_position->x -= current_velocity_component->x;
		}

		if (current_position->y > 0)
		{
			current_position->y += current_velocity_component->y;
		} else if (current_position->y < 0)
		{
			current_position->y -= current_velocity_component->y;
		}
	}
}
