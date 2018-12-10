#include "ColliderSystem.h"

using namespace memecity::engine::ecs;

void ColliderSystem::run(EntityManager& em) const
{
	auto components = em.get_components_of_type<ColliderComponent>();
	QuadTree quad_tree(4, Rectangle(0, 0, _map_width, _map_height));
	for (const ColliderComponent& collider : components)
	{
		quad_tree.insert(collider.boundary_rectangle);
	}

	for (const ColliderComponent& collider : components)
	{
		const auto& boundary_rectangle = collider.boundary_rectangle;
		std::vector<std::reference_wrapper<const BoundaryRectangle>> query_result{};
		query_result.reserve(4);
		quad_tree.query(boundary_rectangle, query_result);
		query_result.shrink_to_fit();
		for (const BoundaryRectangle& collidable : query_result)
		{
			if (&boundary_rectangle != &collidable && intersects(boundary_rectangle, collidable))
			{
				collider_event.fire(em, { collider.entity(), boundary_rectangle, collidable });
			}
		}
	}
}
