#ifndef _DEATH_EVENT_ARGS_H
#define _DEATH_EVENT_ARGS_H
#include <ECS.h>

struct DeathEventArgs : public  memecity::engine::ecs::eventing::EventArgs
{
	DeathEventArgs() {}
};

#endif

