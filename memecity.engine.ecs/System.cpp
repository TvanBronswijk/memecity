#include "System.h"

bool System::is_on_event(Event &e)
{
	return e.get_type() == on_event;
}

std::string System::get_type()
{
	return "abstract system";
}

void System::run(EntityManager &em)
{
}

void System::run(EntityManager &em, Event &e) 
{
}
