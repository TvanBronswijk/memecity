#ifndef _FIGHTINGSYSTEM_H
#define  _FIGHTINGSYSTEM_H
#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "AttackEventArgs.h"
#include "HealthComponent.h"
#include "AIcomponent.h"
#include <cstdlib>

class FightingSystem : public System {

	static std::string SYSTEM_TYPE;

public:
	FightingSystem();

	std::string get_type() override;
	void run(EntityManager &em) override;
	void run(EntityManager &em, EventArgs& e) override;
};

#endif