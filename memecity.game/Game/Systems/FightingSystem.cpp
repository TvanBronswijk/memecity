#include "FightingSystem.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace memecity::engine::ecs;


void FightingSystem::run(EntityManager &em) const {
}

void FightingSystem::on_attack(EntityManager &em, AttackEventArgs args) {
	auto health_target = args.target.get<HealthComponent>();
	auto stats_source = args.source.get<StatsComponent>();
	auto AI = args.target.get<AIComponent>();

	srand(time(NULL));

	//calculate health
	if (stats_source != nullptr){
		health_target->health -= (0 + (rand() % (stats_source->strength - 0)));
	} else {
		health_target->health -= 1;
	}

	if (AI != nullptr) {
		this->damage_event.fire(em, args.target );
		AI->state = AIComponent::State::Fighting;
	}
}
