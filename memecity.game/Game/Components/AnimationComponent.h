﻿#ifndef _ANIMATION_COMPONENT_H
#define _ANIMATION_COMPONENT_H

#include <ECS.h>

struct AnimationComponent : public memecity::engine::ecs::Component
{
	AnimationComponent(memecity::engine::ecs::Entity& entity) : memecity::engine::ecs::Component(entity){}
};

#endif