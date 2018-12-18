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
	auto stats_target = args.target.get<StatsComponent>();
	auto AI = args.target.get<AIComponent>();

	if (args.target.has<PlayerComponent>()) {
		health_changed_event.fire(em, { health_target->health });
		if (health_target->health <= 0) {
			death_event.fire(em, {});
		}
	}
	if (AI != nullptr) {
		if (AI->state != Ai_State::Fighting ) {
			AI->state = Ai_State::Fighting;
		}
		health_target->health -= (rand() % (stats_source->strength * 5) + 1);
		if (health_target->health < 0) { 
			health_target->health = 0; 
			auto luck = rand() % stats_source->luck;
			if (luck > stats_source->luck / 5) {
				exp_event.fire(em, ExpEventArgs((AI->exp * 1.3), 0));
			}
			else {
				exp_event.fire(em, ExpEventArgs(AI->exp, 0));
			}
			AI->exp = 0;
		}
		this->damage_event.fire(em, args.target);
	}
	else {
		auto ai = args.source.get<AIComponent>();
		if (ai->timer_fighting > 0.5) {
			auto attack = (rand() % (stats_source->strength) + 1);
			auto defence = (rand() % (stats_target->agility * 4));
			auto damage = attack - defence;
			if(damage > 0)
			health_target->health -= damage;
			if (health_target->health < 0) health_target->health = 0;

			ai->timer_fighting = 0;

			if (health_target->health == 0) {
				args.source.get<AIComponent>()->state = Ai_State::Idle;
				death_event.fire(em, {});
			}
			health_changed_event.fire(em, { health_target->health });
		}
	}
	this->quest_event.fire(em, { &args.target , nullptr });
}
