#ifndef _MOVESYSTEM_H
#define  _MOVESYSTEM_H
#include "../Components.h"
#include "../Event/ColliderEventArgs.h"
#include "../Event/MoveEventArgs.h"
#include <ECS.h>
class MoveSystem : public memecity::engine::ecs::System
{
public:
	void run(memecity::engine::ecs::EntityManager& em) const override;
	void on_collision(memecity::engine::ecs::EntityManager & em, ColliderEventArgs ea);

	memecity::engine::ecs::eventing::Event<MoveEventArgs> animated_move_event;
};
#endif
