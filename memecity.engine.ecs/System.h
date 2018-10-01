#include <iostream>
#include "Event.h"

class EntityManager;

class System {
private:
	std::string on_event;
public:
	bool isOnEvent(Event &e);
	virtual std::string getType();
	virtual void Run(EntityManager &em);
	virtual void Run(EntityManager &em, Event &e);
};