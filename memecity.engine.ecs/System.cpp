#include "System.h"

bool System::isOnEvent(Event &e)
{
	return e.getType() == on_event;
}

std::string System::getType()
{
	return "abstract system";
}

void System::Run(EntityManager &em)
{
}

void System::Run(EntityManager &em, Event &e) 
{
}
