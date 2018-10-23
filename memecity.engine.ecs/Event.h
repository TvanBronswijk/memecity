#ifndef _EVENT_H
#define  _EVENT_H
#include <iostream>
#include <vector>
#include "System.h"
#include "EventArgs.h"

class Event {
private:
	std::vector<System*> subscribers;
public:
	///<summary>Get the type of the event for filtering.</summary>
	virtual std::string get_type() = 0;

	///<summary>Subscribe a system to this event.</summary>
	void subscribe(System* s)
	{
		subscribers.push_back(s);
	}

	///<summary>Fire the event with args.</summary>
	void fire(EntityManager& em, const EventArgs& ea)
	{
		for (auto s : subscribers)
			s->run(em, ea);
	}

	virtual ~Event() {}
};

#endif
