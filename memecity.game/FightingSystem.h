#ifndef _FIGHTINGSYSTEM_H
#define  _FIGHTINGSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "AttackEventArgs.h"
#include "HealthComponent.h"
#include "AIcomponent.h"
#include <cstdlib>

class FightingSystem : public ecs::System {

public:
	static ecs::system_typetoken SYSTEM_TYPE;
	FightingSystem();
	ecs::system_typetoken get_type_token() const override { return FightingSystem::SYSTEM_TYPE; }
	void run(ecs::EntityManager& em) const override;
};

#endif