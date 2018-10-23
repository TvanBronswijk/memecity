#ifndef _SYSTEM_H
#define  _SYSTEM_H
#include <iostream>
#include "EventArgs.h"

class Event;
class EntityManager;

class System {
private:

public:
	///<summary>Get the type of the System.</summary>
	virtual std::string get_type() = 0;

	///<summary>Do the activity of the System.</summary>
	virtual void run(EntityManager &em) = 0;

	///<summary>Do the activity of the System.</summary>
	virtual void run(EntityManager &em, EventArgs e) = 0;

	virtual ~System(){}

};

#endif