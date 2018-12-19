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

	auto health_component = args.target.get<HealthComponent>();
	auto target_ai_component = args.target.get<AIComponent>();

	const auto source_stats_component = args.source.get<StatsComponent>();
	const auto target_stats_component = args.target.get<StatsComponent>();

	args.source.get<AnimationComponent>()->current_state = AnimationComponent::AnimationState::fighting;

	if (target_ai_component != nullptr)
	{
		if (target_ai_component->state != Ai_State::Fighting ) {
			target_ai_component->state = Ai_State::Fighting;
		}

		health_component->health -= (rand() % (source_stats_component->strength * 5) + 1);
		
		if (health_component->health < 0) {
			health_component->health = 0; 
			exp_event.fire(em, ExpEventArgs(target_ai_component->exp,0));
			death_event.fire(em, { args.target });
			target_ai_component->exp = 0;
		}

		this->damage_event.fire(em, args.target);
	}
	else 
	{
		const auto ai = args.source.get<AIComponent>();
		if (ai->timer_fighting > 0.5) {

			const auto attack = (rand() % (source_stats_component->strength) + 1);
			const auto defense = (rand() % (target_stats_component->agility * 4));
			const auto damage = attack - defense;
			
			if (damage > 0) {
				health_component->health -= damage;
			}

			if (health_component->health < 0) {
				health_component->health = 0;
			}

			ai->timer_fighting = 0;

			if (health_component->health == 0) {
				args.source.get<AIComponent>()->state = Ai_State::Idle;
				death_event.fire(em, {args.target});
			}

			health_changed_event.fire(em, { health_component->health });
		}
	}

	this->quest_event.fire(em, { &args.target , nullptr });
}
