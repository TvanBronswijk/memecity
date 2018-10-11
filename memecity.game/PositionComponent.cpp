#include "PositionComponent.h"

std::string PositionComponent::COMPONENT_TYPE = "PositionComponent";

PositionComponent::PositionComponent(Entity* e) : Component(e)
{
	this->x = 0;
	this->y = 0;
}

PositionComponent::PositionComponent(Entity* e, float x, float y) : Component(e)
{
	this->x = x;
	this->y = y;
}

std::string PositionComponent::get_type()
{
	return COMPONENT_TYPE;
}
