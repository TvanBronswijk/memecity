#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct VelocityComponent : public Component
{
	static std::string COMPONENT_TYPE;

	float x, y;

	VelocityComponent(Entity* e) : VelocityComponent(e, 0.0f, 0.0f) {};
	VelocityComponent(Entity* e, float x, float y) : Component(e) { this->x = x; this->y = y; };
	std::string get_type() override;
};

#endif