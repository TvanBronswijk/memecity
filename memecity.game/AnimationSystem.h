#ifndef _ANIMATION_SYSTEM_H
#define _ANIMATION_SYSTEM_H

#include "PositionComponent.h"
#include "AnimationComponent.h"
#include "DrawableComponent.h"

#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"

class AnimationSystem : public System
{
	static std::string const SYSTEM_TYPE;

public:
	std::string get_type() override;
	void run(EntityManager& em) override;
	void run(EntityManager& em, EventArgs& e) override;
};

#endif
