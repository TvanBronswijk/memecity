#ifndef _ANIMATION_SYSTEM_H
#define _ANIMATION_SYSTEM_H

#include "DrawableComponent.h"

class AnimationSystem : public ecs::System
{

public:
	static ecs::system_typetoken SYSTEM_TYPE;
	void run(ecs::EntityManager& em) const override;
	ecs::system_typetoken get_type_token() const override { return AnimationSystem::SYSTEM_TYPE; }
};

#endif
