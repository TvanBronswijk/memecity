#include "FightingSystem.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "..\..\Assets.h"
#include "../Enum/AIStates.h"

using namespace memecity::engine::ecs;


void FightingSystem::run(EntityManager &em, float dt) const {
	auto npcs = em.get_components_of_type<AIComponent>();

	for (std::vector<std::reference_wrapper<AIComponent>>::iterator it = npcs.begin(); it != npcs.end(); ++it) {
		(*it).get().timer_fighting += dt;
		if ((*it).get().timer_fighting > 5) (*it).get().timer_fighting = 0;
	}
}

void FightingSystem::on_attack(EntityManager &em, AttackEventArgs args) {
	auto health_target = args.target.get<HealthComponent>();
	auto stats_source = args.source.get<StatsComponent>();
	auto AI = args.target.get<AIComponent>();

	if (AI != nullptr) {
		if (AI->state != State::Fighting ) {
			AI->state = State::Fighting;
		}
		health_target->health -= (rand() % (stats_source->strength * 5) + 1);
		if (health_target->health < 0) { 
			health_target->health = 0; 
			//exp_event.fire(em, {AI->exp});
			//TODO::exp
		}
		this->damage_event.fire(em, args.target);
	}
	else {
		auto ai = args.source.get<AIComponent>();
		if (ai->timer_fighting > 0.5) {
			health_target->health -= (rand() % (stats_source->strength)+ 1);
			if (health_target->health < 0) health_target->health = 0;

			ai->timer_fighting = 0;

			if (health_target->health == 0) {
				args.source.get<AIComponent>()->state = State::Idle;
				death_event.fire(em, {});
			}
			health_changed_event.fire(em, { health_target->health });
		}
	}
	this->quest_event.fire(em, { &args.target , nullptr });
}
