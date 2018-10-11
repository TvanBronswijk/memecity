#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct VelocityComponent : public Component
{

public:
	float x, y;
	std::string get_type() override;
	VelocityComponent(Entity* e);
	VelocityComponent(float x, float y, Entity* e);
};

#endif
