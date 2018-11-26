#ifndef _ANIMATION_SYSTEM_H
#define _ANIMATION_SYSTEM_H
#include <ECS.h>
#include "..\Components.h"

struct MoveEventArgs;

class AnimationSystem : public memecity::engine::ecs::System
{
public:
	void run(memecity::engine::ecs::EntityManager& em) const override;
	void on_move(memecity::engine::ecs::EntityManager & em, MoveEventArgs ea);
};

#endif
