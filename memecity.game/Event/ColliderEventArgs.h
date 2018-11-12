#ifndef _COLLIDER_EVENT_ARGS_H
#define _COLLIDER_EVENT_ARGS_H
#include <ECS.h>

struct ColliderEventArgs : public memecity::engine::ecs::eventing::EventArgs
{
	const memecity::engine::ecs::Entity &source, &target;

	ColliderEventArgs(const memecity::engine::ecs::Entity& source, const memecity::engine::ecs::Entity& target) : source(source), target(target) {}
};

#endif
