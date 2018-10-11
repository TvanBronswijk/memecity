#include "VelocityComponent.h"

VelocityComponent::VelocityComponent()
{
	x = 0.0f;
	y = 0.0f;
}

VelocityComponent::VelocityComponent(float x, float y)
{
	this->x = x;
	this->y = y;
}