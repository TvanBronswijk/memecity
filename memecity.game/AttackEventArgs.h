#ifndef _ATTACK_EVENT_ARGS_H
#define _ATTACK_EVENT_ARGS_H
#include "ECS.h"

struct AttackEventArgs : public  ecs::eventing::EventArgs
{
	const ecs::Entity &source, &target;

	AttackEventArgs(const ecs::Entity& source, const ecs::Entity& target) : source(source), target(target) {}
};

#endif
