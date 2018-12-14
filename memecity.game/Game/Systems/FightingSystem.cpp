#include "FightingSystem.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "..\..\Assets.h"
#include "../Enum/AIStates.h"

using namespace memecity::engine::ecs;


void FightingSystem::run(EntityManager &em, float dt) const {
}

void FightingSystem::on_attack(EntityManager &em, AttackEventArgs args) {
	auto health_target = args.target.get<HealthComponent>();
	auto stats_source = args.source.get<StatsComponent>();
	auto AI = args.target.get<AIComponent>();

	//calculate health
	if (stats_source != nullptr){
		health_target->health -= (rand() % (stats_source->strength * 5));
		if (health_target->health < 0) health_target->health = 0;
	} else {
		health_target->health -= 1;
	}

	if (AI != nullptr) {
		if (AI->state != State::Fighting) {
			AI->state = State::Fighting;
		}
		else {
			this->damage_event.fire(em, args.target); 
		}
	}
	else{
		const auto animation_component = args.source.get<AnimationComponent>();
		if (animation_component)
		{
			animation_component->current_state = AnimationComponent::AnimationState::fighting;
		}

		if (health_target->health == 0) {
			args.source.get<AIComponent>()->state = State::Idle;
			death_event.fire(em, {});
		}
		health_changed_event.fire(em, { health_target->health });
	}

	this->quest_event.fire(em, { &args.target , nullptr });
}
