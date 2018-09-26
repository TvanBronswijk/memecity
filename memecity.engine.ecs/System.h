#include <iostream>
#include "Event.h"

class System {
private:
	std::string on_event;
public:
	bool event_based;
	bool isOnEvent(Event e);
	virtual std::string getType();
	virtual void Run();
};