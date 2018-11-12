#ifndef _ATTACK_EVENT_ARGS_H
#define _ATTACK_EVENT_ARGS_H
#include "ECS.h"

struct AttackEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	const memecity::engine::ecs::Entity &source, &target;

	AttackEventArgs(const memecity::engine::ecs::Entity& source, const memecity::engine::ecs::Entity& target) : source(source), target(target) {}
};

#endif
