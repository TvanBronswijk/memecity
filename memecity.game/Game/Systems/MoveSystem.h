#ifndef _MOVESYSTEM_H
#define  _MOVESYSTEM_H
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\ColliderEventArgs.h"
#include "../Event/MoveEventArgs.h"

class MoveSystem : public memecity::engine::ecs::System
{
public:
	memecity::engine::ecs::eventing::Event<MoveEventArgs> move_event;

	void run(memecity::engine::ecs::EntityManager& em) const override;
	void on_collision(memecity::engine::ecs::EntityManager & em, ColliderEventArgs ea) const;
};
#endif
