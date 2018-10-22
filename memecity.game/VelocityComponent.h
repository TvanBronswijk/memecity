#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct VelocityComponent : Component
{
	static std::string COMPONENT_TYPE;

	float x, y;

	VelocityComponent(Entity* e);
	VelocityComponent(Entity* e, float x, float y);
	std::string get_type() override;
};

#endif