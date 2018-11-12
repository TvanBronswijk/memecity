#ifndef _ANIMATION_SYSTEM_H
#define _ANIMATION_SYSTEM_H
#include <ECS.h>

class AnimationSystem : public memecity::engine::ecs::System
{
public:
	void run(memecity::engine::ecs::EntityManager& em) const override;
};

#endif
