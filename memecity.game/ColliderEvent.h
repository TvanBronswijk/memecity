#ifndef _COLLIDER_EVENT_H
#define _COLLIDER_EVENT_H
#include <Event.h>

class ColliderEvent : public Event
{
	static std::string EVENT_TYPE;

public:
	std::string get_type() override;
	ColliderEvent();
	~ColliderEvent();
};
#endif