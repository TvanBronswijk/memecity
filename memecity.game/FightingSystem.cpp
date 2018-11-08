#include "FightingSystem.h"


std::string FightingSystem::SYSTEM_TYPE = "FightingSystem";


FightingSystem::FightingSystem() {
}



std::string FightingSystem::get_type() {
	return SYSTEM_TYPE;
}
void FightingSystem::run(EntityManager &em) {
}
void FightingSystem::run(EntityManager &em, EventArgs& e) {
	const auto attack_event_args = static_cast<AttackEventArgs&>(e);
	HealthComponent* health_source = dynamic_cast<HealthComponent*>(em.get_component_of_entity(attack_event_args.source_entity_id, HealthComponent::COMPONENT_TYPE));
	HealthComponent* health_target = dynamic_cast<HealthComponent*>(em.get_component_of_entity(attack_event_args.target_entity_id, HealthComponent::COMPONENT_TYPE));
	AIComponent* AI = dynamic_cast<AIComponent*>(em.get_component_of_entity(attack_event_args.target_entity_id, AIComponent::COMPONENT_TYPE));

	if (AI != nullptr) {
		AI->_state = AI->FIGHTING;
	}

	health_target->_health -= 10;
}