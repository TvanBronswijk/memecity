#ifndef _INTERACTION_EVENT_H
#define _INTERACTION_EVENT_H
#include <Event.h>

class InteractionEvent : public Event
{
	static std::string EVENT_TYPE;

public:
	std::string get_type() override;
	InteractionEvent();
	~InteractionEvent();
};
#endif
