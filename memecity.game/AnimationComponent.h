#ifndef _ANIMATION_COMPONENT_H
#define _ANIMATION_COMPONENT_H
#include "ECS/Component.h"


struct AnimationComponent : public ecs::Component
{
	bool is_fighting = false;

	AnimationComponent(const ecs::Entity& entity) : ecs::Component(entity){}
};

#endif