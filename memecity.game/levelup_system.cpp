#include <string>
#include "levelup_system.h"


levelup_system::levelup_system()
{
}


levelup_system::~levelup_system()
{
}

bool levelup_system::is_on_event(Event* e)//idk
{
	return false;
}

std::string levelup_system::get_type()
{
	return std::string("levelup_system");
}

void levelup_system::run(EntityManager& em)//60 p/s
{

}

void levelup_system::run(EntityManager& em, Event* e)//deze yoeri
{

}
