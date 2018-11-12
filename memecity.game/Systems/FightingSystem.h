#ifndef _FIGHTINGSYSTEM_H
#define  _FIGHTINGSYSTEM_H
#include <ECS.h>
#include "..\Components.h"
#include "..\Event\AttackEventArgs.h"

class FightingSystem : public memecity::engine::ecs::System {

public:
	void on_attack(memecity::engine::ecs::EntityManager& em, AttackEventArgs args);
	void run(memecity::engine::ecs::EntityManager& em) const override;
};

#endif
