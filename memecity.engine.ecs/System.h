#include <iostream>
#include "Event.h"

class EntityManager;

class System {
private:
	std::string on_event;
public:
	///<summary>Check if the System is based a certain event.</summary>
	bool is_on_event(Event &e);

	///<summary>Get the type of the System.</summary>
	virtual std::string get_type();

	///<summary>Do the activity of the System.</summary>
	virtual void run(EntityManager &em);

	///<summary>Do the activity of the System.</summary>
	virtual void run(EntityManager &em, Event &e);
};