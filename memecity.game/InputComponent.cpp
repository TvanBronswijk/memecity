#include "InputComponent.h"

std::string InputComponent::COMPONENT_TYPE = "InputComponent";

InputComponent::InputComponent(Entity* e) : Component(e)
{
	
}

std::string InputComponent::get_type()
{
	return COMPONENT_TYPE;
}
