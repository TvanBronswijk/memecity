#ifndef _ANIMATION_SYSTEM_H
#define _ANIMATION_SYSTEM_H

#include "ECS/System.h"

class AnimationSystem : public ecs::System
{
public:
	void run(ecs::EntityManager& em) const override;
};

#endif
