#ifndef _COLLIDERCOMPONENT_H
#define _COLLIDERCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "../memecity.engine/Texture.h"

struct ColliderComponent : public Component
{
	static std::string COMPONENT_TYPE;

	int x, y, w, h, x2, y2;

	ColliderComponent(Entity *e) : ColliderComponent(e, 0, 0, 0, 0) {};
	ColliderComponent(Entity *e, int x, int y, int w, int h) : Component(e)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
		this->x2 = x + w - 1;
		this->y2 = y + h - 1;
	};

	std::string get_type() override;
};

#endif