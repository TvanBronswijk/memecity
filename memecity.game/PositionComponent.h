#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct PositionComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	float x, y, diffx, diffy;
	PositionComponent(ecs::Entity& e) : PositionComponent(e, 0.0f, 0.0f ) {};
	PositionComponent(ecs::Entity& e, float x, float y) : ecs::Component(e) 
	{ 
		this->x = x; 
		this->y = y; 
		this->diffx = 0.0f; 
		this->diffy = 0.0f; 
	};
	ecs::component_typetoken get_type_token() override { return PositionComponent::COMPONENT_TYPE; }
};

#endif