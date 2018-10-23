#include "ExpComponent.h"

std::string ExpComponent::COMPONENT_TYPE = "ExpComponent";

ExpComponent::ExpComponent(Entity* e): Component(e)
{
}

std::string ExpComponent::get_type()
{
	return std::string("ExpComponent");
}


ExpComponent::~ExpComponent()
{
}
