#include "FightingSystem.h"

#include "HealthComponent.h"
#include "AIcomponent.h"

using namespace memecity::engine::ecs;


void FightingSystem::run(EntityManager &em) const {
}

void FightingSystem::on_attack(EntityManager &em, AttackEventArgs args) {
	auto health_source = args.source.get<HealthComponent>();
	auto health_target = args.target.get<HealthComponent>();
	auto AI = args.target.get<AIComponent>();

	if (AI != nullptr) {
		AI->state = AIComponent::State::Fighting;
	}

	health_target->health -= 10;
}
