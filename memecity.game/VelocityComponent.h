#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct VelocityComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	float x, y;
	VelocityComponent(ecs::Entity* e) : VelocityComponent(e, 0.0f, 0.0f) {};
	VelocityComponent(ecs::Entity* e, float x, float y) : ecs::Component(e) 
	{ 
		this->x = x; 
		this->y = y; 
	};
	ecs::component_typetoken get_type_token() override { return VelocityComponent::COMPONENT_TYPE; }
};

#endif