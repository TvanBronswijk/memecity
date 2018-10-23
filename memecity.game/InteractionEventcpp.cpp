#include "InteractionEvent.h"

std::string InteractionEvent::EVENT_TYPE = "ColliderComponent";


std::string InteractionEvent::get_type()
{
	return EVENT_TYPE;
}

InteractionEvent::InteractionEvent()
{
}

InteractionEvent::~InteractionEvent()
{
}