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

int VelocityComponent::get_speed() const
{
	return this->speed;
}

void VelocityComponent::set_speed(int speed)
{
	this->speed = speed;
}

float VelocityComponent::get_x() const
{
	return this->x;
}

void VelocityComponent::set_x(float x)
{
	this->x = x;
}

float VelocityComponent::get_y() const
{
	return this->y;
}

void VelocityComponent::set_y(float y)
{
	this->y = y;
}
