#include "PositionComponent.h"

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