#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct VelocityComponent : Component
{
	float x, y;

	VelocityComponent();
	VelocityComponent(float x, float y);
};

#endif