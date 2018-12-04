#include "ColliderSystem.h"

using namespace memecity::engine::ecs;

void ColliderSystem::run(EntityManager& em) const
{
	auto entities = em.get_entities_with_component<ColliderComponent>();
	QuadTree quad_tree(4, Rectangle(0, 0, _map_width, _map_height));
	for (const Entity& entity : entities)
	{
		quad_tree.insert(entity.get<ColliderComponent>()->boundary_rectangle);
	}

	for (const Entity& entity : entities)
	{
		auto& boundary_rectangle = entity.get<ColliderComponent>()->boundary_rectangle;
		
		std::vector<const BoundaryRectangle*> query_result{};
		quad_tree.query(boundary_rectangle, query_result);
		for (const BoundaryRectangle* element : query_result)
		{
			if (intersects(boundary_rectangle, *element))
			{
				collider_event.fire(em, { entity, boundary_rectangle, *element });
			}
		}
	}
}
