#ifndef _INTERACTION_EVENT_ARGS_H
#define _INTERACTION_EVENT_ARGS_H
#include "EventArgs.h"

struct InteractionEventArgs : public EventArgs
{
	static std::string EVENT_ARGS_TYPE;

public:
	int source_entity_id;
	std::string get_type();
	InteractionEventArgs(int source_entity_id);
};

#endif
