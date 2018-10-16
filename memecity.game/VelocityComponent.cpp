#include "VelocityComponent.h"

std::string VelocityComponent::get_type() {
	return"VelocityComponent";
}

VelocityComponent::VelocityComponent(Entity* e) : Component(e)
{
	this->entity_id = e->id;
	x = 0.0f;
	y = 0.0f;
}

VelocityComponent::VelocityComponent(float x, float y, Entity* e) : Component(e)
{
	this->entity_id = e->id;
	this->x = x;
	this->y = y;
}
