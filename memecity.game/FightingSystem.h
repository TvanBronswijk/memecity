#ifndef _FIGHTINGSYSTEM_H
#define  _FIGHTINGSYSTEM_H
#include <ECS.h>
#include "AttackEventArgs.h"

class FightingSystem : public ecs::System {

public:
	static ecs::system_typetoken SYSTEM_TYPE;
	FightingSystem();
	ecs::system_typetoken get_type_token() const override { return FightingSystem::SYSTEM_TYPE; }
	void attack(ecs::EntityManager& em, AttackEventArgs args);
	void run(ecs::EntityManager& em) const override;
};

#endif