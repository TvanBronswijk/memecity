#include "ColliderSystem.h"
#include "MoveSystem.h"

ecs::system_typetoken ColliderSystem::SYSTEM_TYPE = "ColliderSystem";

void ColliderSystem::run(ecs::EntityManager& em) const
{
	auto components = em.get_components_of_type<ColliderComponent>(ColliderComponent::COMPONENT_TYPE);

	for (auto collider_component_ref : components)
	{
		auto& collider_component = collider_component_ref.get();

		for (auto other_collider_component_ref : components)
		{
			auto& other_collider_component = other_collider_component_ref.get();

			if (collider_component.entity != other_collider_component.entity)
			{
				auto current_location_component =
					em.get_component_of_entity<PositionComponent>(collider_component.entity, PositionComponent::COMPONENT_TYPE);

				auto other_location_component =
					em.get_component_of_entity<PositionComponent>(other_collider_component.entity, PositionComponent::COMPONENT_TYPE);

				int current_x1, current_y1, current_x2, current_y2;
				int other_x1, other_y1, other_x2, other_y2;

				current_x1 = current_location_component->x;
				current_y1 = current_location_component->y;
				current_x2 = current_location_component->x + collider_component.w - 1;
				current_y2 = current_location_component->y + collider_component.h - 1;

				other_x1 = other_location_component->x;
				other_y1 = other_location_component->y;
				other_x2 = other_location_component->x + other_collider_component.w - 1;
				other_y2 = other_location_component->y + other_collider_component.h - 1;

				if (current_x1 < other_x2 &&
					current_y1 < other_y2 &&
					other_x1 < current_x2 &&
					other_y1 < current_y2)
				{
					collider_event.fire(em, { collider_component.entity, other_collider_component.entity });
				}
			}
		}
	}
}