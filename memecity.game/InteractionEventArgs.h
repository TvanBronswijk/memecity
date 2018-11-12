#ifndef _INTERACTION_EVENT_ARGS_H
#define _INTERACTION_EVENT_ARGS_H
#include "ECS.h"

struct InteractionEventArgs : public memecity::engine::ecs::eventing::EventArgs
{
	const memecity::engine::ecs::Entity &source;

	InteractionEventArgs(const memecity::engine::ecs::Entity& source) : source(source) {}

};

#endif
