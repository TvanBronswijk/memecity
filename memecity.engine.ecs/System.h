#include <iostream>
#include "Event.h"

class EntityManager;

class System {
private:
	std::string on_event;
public:
	bool is_on_event(Event &e);
	virtual std::string get_type();
	virtual void run(EntityManager &em);
	virtual void run(EntityManager &em, Event &e);
};