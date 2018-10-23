#include "ColliderEvent.h"

std::string ColliderEvent::EVENT_TYPE = "ColliderComponent";


std::string ColliderEvent::get_type()
{
	return EVENT_TYPE;
}

ColliderEvent::ColliderEvent()
{
}

ColliderEvent::~ColliderEvent()
{
}
