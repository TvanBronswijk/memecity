#ifndef _ANIMATION_SYSTEM_H
#define _ANIMATION_SYSTEM_H

#include "PositionComponent.h"
#include "AnimationComponent.h"
#include "DrawableComponent.h"

#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"

class AnimationSystem : public ecs::System
{

public:
	static ecs::system_typetoken SYSTEM_TYPE;
	void run(ecs::EntityManager& em) const override;
	ecs::system_typetoken get_type_token() const override { return AnimationSystem::SYSTEM_TYPE; }
};

#endif
