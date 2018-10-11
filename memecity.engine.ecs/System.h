#ifndef _SYSTEM_H
#define  _SYSTEM_H
#include <iostream>
#include "Event.h"

class EntityManager;

class System {
private:

public:
	///<summary>Check if the System is based a certain event.</summary>
	virtual bool is_on_event(Event *e) = 0;

	///<summary>Get the type of the System.</summary>
	virtual std::string get_type() = 0;

	///<summary>Do the activity of the System.</summary>
	virtual void run(EntityManager &em) = 0;

	///<summary>Do the activity of the System.</summary>
	virtual void run(EntityManager &em, Event *e) = 0;
};

#endif