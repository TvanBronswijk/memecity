#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct PositionComponent : public Component
{
	static std::string COMPONENT_TYPE;

	float x, y;

	PositionComponent(Entity* e) : PositionComponent(e, 0.0f, 0.0f) {};
	PositionComponent(Entity* e, float x, float y) : Component(e) { this->x = x; this->y = y; };
	std::string get_type() override;
};

#endif