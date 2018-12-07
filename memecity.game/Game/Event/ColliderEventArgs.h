#ifndef _COLLIDER_EVENT_ARGS_H
#define _COLLIDER_EVENT_ARGS_H
#include <ECS.h>
#include <Engine\Collision\BoundaryRectangle.h>

struct ColliderEventArgs : public memecity::engine::ecs::eventing::EventArgs
{
	const memecity::engine::ecs::Entity &source;
	const BoundaryRectangle &source_rectangle, &target_rectangle;

	ColliderEventArgs(const memecity::engine::ecs::Entity& source, const BoundaryRectangle &source_rectangle, const BoundaryRectangle &target_rectangle)
		: source(source), source_rectangle(source_rectangle), target_rectangle(target_rectangle) {}
};

#endif
