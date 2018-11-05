#ifndef _ATTACK_EVENT_H
#define _ATTACK_EVENT_H
#include <Event.h>

class AttackEvent : public Event
{
	static std::string EVENT_TYPE;

public:
	std::string get_type() override;
	AttackEvent();
	~AttackEvent();
};
#endif
