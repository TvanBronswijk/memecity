#include "VelocityComponent.h"

std::string VelocityComponent::COMPONENT_TYPE = "VelocityComponent";

VelocityComponent::VelocityComponent(Entity* e) : Component(e)
{
	x = 0.0f;
	y = 0.0f;
}

VelocityComponent::VelocityComponent(Entity* e, float x, float y) : Component(e)
{
	this->x = x;
	this->y = y;
}

std::string VelocityComponent::get_type()
{
	return COMPONENT_TYPE;
}
