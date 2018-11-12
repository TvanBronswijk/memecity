#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include <ECS.h>

struct VelocityComponent : public memecity::engine::ecs::Component
{
	float x, y;
	VelocityComponent(const memecity::engine::ecs::Entity& entity) : VelocityComponent(entity, 0.0f, 0.0f) {};
	VelocityComponent(const memecity::engine::ecs::Entity& entity, float x, float y) 
		: memecity::engine::ecs::Component(entity), x(x), y(y) {};
};

#endif
