#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include "Component.h"

struct PositionComponent : public Component
{
	float x, y;
	PositionComponent();
	PositionComponent(float x, float y);
};

#endif
