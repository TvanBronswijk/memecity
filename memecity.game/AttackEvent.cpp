#include "AttackEvent.h"

std::string AttackEvent::EVENT_TYPE = "AttackEvent";


std::string AttackEvent::get_type()
{
	return EVENT_TYPE;
}

AttackEvent::AttackEvent()
{
}

AttackEvent::~AttackEvent()
{
}