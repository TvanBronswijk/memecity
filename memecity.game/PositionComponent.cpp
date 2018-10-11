#include "PositionComponent.h"

std::string PositionComponent::get_type() {
	return"PositionComponent";
}

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
