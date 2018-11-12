#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include <ECS.h>

struct PositionComponent : public ecs::Component
{
	float x, y, diffx, diffy;
	PositionComponent(const ecs::Entity& entity) 
		: PositionComponent(entity, 0.0f, 0.0f) {};
	PositionComponent(const ecs::Entity& entity, float x, float y) 
		: ecs::Component(entity), x(x), y(y), diffx(0.0f), diffy(0.0f) {};
};

#endif
