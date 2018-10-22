#include "exp_system.h"
#include <string>


exp_system::exp_system()
{
}


exp_system::~exp_system()
{
}

bool exp_system::is_on_event(Event* e)
{
	return true;
}

std::string exp_system::get_type()
{
	return std::string("exp_system");
}

void exp_system::run(EntityManager& em)
{
}

void exp_system::run(EntityManager& em, Event* e)
{
}
