#ifndef _COLLIDERCOMPONENT_H
#define _COLLIDERCOMPONENT_H
#include "ECS.h"

struct ColliderComponent : public ecs::Component
{
	int w, h;

	ColliderComponent(const ecs::Entity& entity) : ColliderComponent(entity, 0, 0) {};
	ColliderComponent(const ecs::Entity& entity, int w, int h) : ecs::Component(entity), w(w), h(h) {};
};

#endif