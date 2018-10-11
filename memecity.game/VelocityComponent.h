#ifndef _VELOCITYCOMPONENT_H
#define  _VELOCITYCOMPONENT_H
#include "Component.h"

class VelocityComponent : Component
{
private:
	int speed;
	float x, y;
public:
	VelocityComponent();
	VelocityComponent(int speed);
	VelocityComponent(float x, float y);
	VelocityComponent(int speed, float x, float y);
	int get_speed() const;
	void set_speed(int speed);
	float get_x() const;
	void set_x(float x);
	float get_y() const;
	void set_y(float y);

};

#endif