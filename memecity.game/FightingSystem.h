#ifndef _FIGHTINGSYSTEM_H
#define  _FIGHTINGSYSTEM_H
#include <ECS.h>
#include "AttackEventArgs.h"

class FightingSystem : public ecs::System {

public:
	void attack(ecs::EntityManager& em, AttackEventArgs args);
	void run(ecs::EntityManager& em) const override;
};

#endif