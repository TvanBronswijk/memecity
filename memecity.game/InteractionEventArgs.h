#ifndef _INTERACTION_EVENT_ARGS_H
#define _INTERACTION_EVENT_ARGS_H
#include "ECS.h"

struct InteractionEventArgs : public ecs::eventing::EventArgs
{
	const ecs::Entity &source;

	InteractionEventArgs(const ecs::Entity& source) : source(source) {}

};

#endif
