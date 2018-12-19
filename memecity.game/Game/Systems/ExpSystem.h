#ifndef _EXP_SYSTEM_H
#define _EXP_SYSTEM_H
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\ExpEventArgs.h"
#include "../Event/StatsEventArgs.h"

class ExpSystem: public memecity::engine::ecs::System
{
public:
	void run(memecity::engine::ecs::EntityManager& em, float dt) const override;
	void on_exp_gain(memecity::engine::ecs::EntityManager& em, ExpEventArgs args);
	memecity::engine::ecs::eventing::Event<ExpEventArgs> exp_event;
	memecity::engine::ecs::eventing::Event<StatsEventArgs> stats_changed_event;
};
#endif
