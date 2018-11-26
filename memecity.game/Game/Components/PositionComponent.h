﻿#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include <ECS.h>

struct PositionComponent : public memecity::engine::ecs::Component
{
	float x, y, diffx, diffy;
	PositionComponent(memecity::engine::ecs::Entity& entity) 
		: PositionComponent(entity, 0.0f, 0.0f) {};
	PositionComponent(memecity::engine::ecs::Entity& entity, float x, float y) 
		: memecity::engine::ecs::Component(entity), x(x), y(y), diffx(0.0f), diffy(0.0f) {};
};

#endif