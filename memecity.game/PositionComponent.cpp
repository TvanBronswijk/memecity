#include "PositionComponent.h"

PositionComponent::PositionComponent()
{
	x_position = 0;
	y_position = 0;
}

PositionComponent::PositionComponent(float x, float y)
{
	x_position = x;
	y_position = y;
}

void PositionComponent::update()
{
	x_position++;
	y_position++;
}

float PositionComponent::get_x_position() const
{
	return x_position;
}

void PositionComponent::set_x_position(float x)
{
	x_position = x;
}

float PositionComponent::get_y_position() const
{
	return y_position;
}

void PositionComponent::set_y_position(float y)
{
	y_position = y;
}

void PositionComponent::set_position(float x, float y)
{
	x_position = x;
	y_position = y;
}
