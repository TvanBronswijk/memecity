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
	auto health_source = dynamic_cast<HealthComponent*>(em.get_component_of_entity(attack_event_args.source_entity_id, HealthComponent::COMPONENT_TYPE));
	auto health_target = dynamic_cast<HealthComponent*>(em.get_component_of_entity(attack_event_args.target_entity_id, HealthComponent::COMPONENT_TYPE));

	health_target->_health -= 10;
}