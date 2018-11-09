#ifndef _ANIMATION_COMPONENT_H
#define _ANIMATION_COMPONENT_H

#include "../memecity.engine.ecs/Component.h"
#include "AnimatedTexture.h"

struct AnimationComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	bool is_fighting = false;

	AnimationComponent(const ecs::Entity& entity) : ecs::Component(entity){}
	ecs::component_typetoken get_type_token() const override { return AnimationComponent::COMPONENT_TYPE; }
};

#endif