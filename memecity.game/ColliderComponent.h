#ifndef _COLLIDERCOMPONENT_H
#define _COLLIDERCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "../memecity.engine/Texture.h"

struct ColliderComponent : public Component
{
	static std::string COMPONENT_TYPE;
	Texture *texture;

	ColliderComponent(Entity *e);
	ColliderComponent(Entity *e, Texture *texture);
	std::string get_type() override;
};

#endif