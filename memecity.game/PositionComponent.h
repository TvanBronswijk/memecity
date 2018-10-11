#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct PositionComponent : public Component
{
	float x, y;
	PositionComponent(Entity* e);
	PositionComponent(Entity* e, float x, float y);
};

#endif