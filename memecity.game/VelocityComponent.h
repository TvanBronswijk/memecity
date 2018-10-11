#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include "Component.h"

struct VelocityComponent : Component
{
	int speed;
	float x, y;

	VelocityComponent();
	VelocityComponent(int speed);
	VelocityComponent(float x, float y);
	VelocityComponent(int speed, float x, float y);
};

#endif