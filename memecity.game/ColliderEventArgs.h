#ifndef _COLLIDER_EVENT_ARGS_H
#define _COLLIDER_EVENT_ARGS_H
#include "EventArgs.h"

struct ColliderEventArgs : public EventArgs
{
	static std::string EVENT_ARGS_TYPE;

	int source_entity_id, target_entity_id;

	std::string get_type() override
	{
		return EVENT_ARGS_TYPE;
	}

	ColliderEventArgs(int source_entity_id, int target_entity_id)
	{
		this->source_entity_id = source_entity_id;
		this->target_entity_id = target_entity_id;
	}
};

#endif