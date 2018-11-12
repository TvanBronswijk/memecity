#ifndef _COLLIDER_EVENT_ARGS_H
#define _COLLIDER_EVENT_ARGS_H
#include "ECS.h"

struct ColliderEventArgs : public ecs::eventing::EventArgs
{
	const ecs::Entity &source, &target;

	ColliderEventArgs(const ecs::Entity& source, const ecs::Entity& target) : source(source), target(target) {}
};

#endif