#ifndef _DIMENSION_COMPONENT_H
#define _DIMENSION_COMPONENT_H

#include <ECS.h>

struct DimensionComponent : public memecity::engine::ecs::Component
{
	float w, h;

	DimensionComponent(memecity::engine::ecs::Entity& entity) : DimensionComponent(entity, 0, 0) {};
	DimensionComponent(memecity::engine::ecs::Entity& entity, float w, float h)
		: memecity::engine::ecs::Component(entity), w(w), h(h) {};
};

#endif
