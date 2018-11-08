#ifndef _COLLIDERCOMPONENT_H
#define _COLLIDERCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct ColliderComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	int w, h;

	ColliderComponent(const ecs::Entity& entity) : ColliderComponent(entity, 0, 0) {};
	ColliderComponent(const ecs::Entity& entity, int w, int h) : ecs::Component(entity)
	{
		this->w = w;
		this->h = h;
	};

	ecs::component_typetoken get_type_token() const override { return ColliderComponent::COMPONENT_TYPE; }

};

#endif