#ifndef _ATTACK_EVENT_ARGS_H
#define _ATTACK_EVENT_ARGS_H
#include "EventArgs.h"

struct AttackEventArgs : public EventArgs
{
	static std::string EVENT_ARGS_TYPE;

public:
	int source_entity_id;
	int target_entity_id;
	std::string get_type();
	AttackEventArgs(int source_entity_id, int target_entity_id);
	~AttackEventArgs();
};

#endif
