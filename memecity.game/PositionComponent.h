#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include <ECS.h>

struct PositionComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	float x, y, diffx, diffy;
	PositionComponent(const ecs::Entity& entity) : PositionComponent(entity, 0.0f, 0.0f ) {};
	PositionComponent(const ecs::Entity& entity, float x, float y) : ecs::Component(entity) 
	{ 
		this->x = x; 
		this->y = y; 
		this->diffx = 0.0f; 
		this->diffy = 0.0f; 
	};
	ecs::component_typetoken get_type_token() const override { return PositionComponent::COMPONENT_TYPE; }
};

#endif