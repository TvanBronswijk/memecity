#ifndef _DEATH_EVENT_ARGS_H
#define _DEATH_EVENT_ARGS_H

#include <ECS.h>

struct DeathEventArgs : memecity::engine::ecs::eventing::EventArgs
{
	const memecity::engine::ecs::Entity &target;

	DeathEventArgs(const memecity::engine::ecs::Entity& target) : target(target) {}
};

#endif