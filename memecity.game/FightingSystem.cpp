#include "FightingSystem.h"

#include "HealthComponent.h"
#include "AIcomponent.h"

using namespace ecs;

system_typetoken FightingSystem::SYSTEM_TYPE = "FightingSystem";


FightingSystem::FightingSystem() {
}

void FightingSystem::run(EntityManager &em) const {
}

void FightingSystem::attack(EntityManager &em, AttackEventArgs args) {
	auto health_source = em.get_component_of_entity<HealthComponent>(args.source.id, HealthComponent::COMPONENT_TYPE);
	auto health_target = em.get_component_of_entity<HealthComponent>(args.target.id, HealthComponent::COMPONENT_TYPE);
	auto AI = em.get_component_of_entity<AIComponent>(args.target.id, AIComponent::COMPONENT_TYPE);

	if (AI != nullptr) {
		AI->_state = AI->Fighting;
	}

	health_target->_health -= 10;
}