#include "PlayerComponent.h"

std::string PlayerComponent::COMPONENT_TYPE = "PlayerComponent";

std::string PlayerComponent::get_type()
{
	return COMPONENT_TYPE;
}
