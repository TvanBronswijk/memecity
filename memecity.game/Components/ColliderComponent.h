#ifndef _COLLIDER_COMPONENT_H
#define _COLLIDER_COMPONENT_H

#include <ECS.h>
#include <BoundaryRectangle.h>

struct ColliderComponent : public memecity::engine::ecs::Component
{
	BoundaryRectangle boundary_rectangle;

	ColliderComponent(const memecity::engine::ecs::Entity& e, BoundaryRectangle boundary_rectangle)
		: memecity::engine::ecs::Component(e), boundary_rectangle(boundary_rectangle) {}
	~ColliderComponent() = default;
};

#endif