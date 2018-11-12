#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include <ECS.h>

struct VelocityComponent : public ecs::Component
{
	float x, y;
	VelocityComponent(const ecs::Entity& entity) : VelocityComponent(entity, 0.0f, 0.0f) {};
	VelocityComponent(const ecs::Entity& entity, float x, float y) 
		: ecs::Component(entity), x(x), y(y) {};
};

#endif
