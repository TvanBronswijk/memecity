#include "VelocityComponent.h"

VelocityComponent::VelocityComponent()
{
	speed = 0;
	x = 0.0f;
	y = 0.0f;
}

VelocityComponent::VelocityComponent(int speed)
{
	this->speed = speed;
}

VelocityComponent::VelocityComponent(float x, float y)
{
	this->x = x;
	this->y = y;
	speed = 0;
}


VelocityComponent::VelocityComponent(int speed, float x, float y)
{
	this->speed = speed;
	this->x = x;
	this->y = y;
}