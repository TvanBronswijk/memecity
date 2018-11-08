#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include <ECS.h>

struct VelocityComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	float x, y;
	VelocityComponent(const ecs::Entity& entity) : VelocityComponent(entity, 0.0f, 0.0f) {};
	VelocityComponent(const ecs::Entity& entity, float x, float y) : ecs::Component(entity) 
	{ 
		this->x = x; 
		this->y = y; 
	};
	ecs::component_typetoken get_type_token() const override { return VelocityComponent::COMPONENT_TYPE; }
};

#endif