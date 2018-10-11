#ifndef _POSITIONCOMPONENT_H
#define  _POSITIONCOMPONENT_H
#include "Component.h"

class PositionComponent : public Component
{
protected:
	float x_position, y_position;

public:
	PositionComponent();
	PositionComponent(float x, float y);
	void update();
	float get_x_position() const;
	void set_x_position(float x);
	float get_y_position() const;
	void set_y_position(float y);
	void set_position(float x, float y);
};

#endif
