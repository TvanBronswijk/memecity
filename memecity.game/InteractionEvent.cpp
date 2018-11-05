#include "InteractionEvent.h"

std::string InteractionEvent::EVENT_TYPE = "InteractionEvent";


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