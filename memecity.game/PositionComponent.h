#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct PositionComponent : public Component
{
	
public:
	float x_position, y_position;
	std::string get_type() override;
	PositionComponent();
	PositionComponent(float x, float y);
	void update();
};

#endif
