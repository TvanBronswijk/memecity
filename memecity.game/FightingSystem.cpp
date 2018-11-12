#include "FightingSystem.h"

#include "HealthComponent.h"
#include "AIcomponent.h"

using namespace ecs;


void FightingSystem::run(EntityManager &em) const {
}

void FightingSystem::attack(EntityManager &em, AttackEventArgs args) {
	auto health_source = args.source.get<HealthComponent>();
	auto health_target = args.target.get<HealthComponent>();
	auto AI = args.target.get<AIComponent>();

	if (AI != nullptr) {
		AI->_state = AI->Fighting;
	}

	health_target->_health -= 10;
}