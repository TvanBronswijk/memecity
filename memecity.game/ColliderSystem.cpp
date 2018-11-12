#include "ColliderSystem.h"
#include "MoveSystem.h"
#include "PositionComponent.h"

void ColliderSystem::run(ecs::EntityManager& em) const
{
	auto entities = em.get_entities_with_component<ColliderComponent>();

	for (auto& entity_ref : entities)
	{
		auto& entity = entity_ref.get();

		for (auto& other_entity_ref : entities)
		{
			auto& other_entity = other_entity_ref.get();

			if (entity != other_entity)
			{
				auto collider_component = entity.get<ColliderComponent>();
				auto other_collider_component = other_entity.get<ColliderComponent>();
				auto current_location_component = entity.get<PositionComponent>();
				auto other_location_component = other_entity.get<PositionComponent>();

				if (current_location_component != nullptr && other_location_component != nullptr)
				{
					int current_x1, current_y1, current_x2, current_y2;
					int other_x1, other_y1, other_x2, other_y2;

					current_x1 = current_location_component->x;
					current_y1 = current_location_component->y;
					current_x2 = current_location_component->x + collider_component->w - 1;
					current_y2 = current_location_component->y + collider_component->h - 1;

					other_x1 = other_location_component->x;
					other_y1 = other_location_component->y;
					other_x2 = other_location_component->x + other_collider_component->w - 1;
					other_y2 = other_location_component->y + other_collider_component->h - 1;

					if (current_x1 < other_x2 &&
						current_y1 < other_y2 &&
						other_x1 < current_x2 &&
						other_y1 < current_y2)
					{
						collider_event.fire(em, { entity, other_entity });
					}
				}
			}
		}
	}
}
