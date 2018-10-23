#include "FightingSystem.h"


std::string FightingSystem::SYSTEM_TYPE = "FightingSystem";


FightingSystem::FightingSystem() {
}

bool FightingSystem::is_on_event(Event *e) {
	return false;
}


std::string FightingSystem::get_type() {
	return SYSTEM_TYPE;
}
void FightingSystem::run(EntityManager &em) {
}
void FightingSystem::run(EntityManager &em, Event *e) {
	/*auto vector = em.get_entities_with_component(AIComponent::COMPONENT_TYPE);// change to player

	for (auto & element : vector) {
		AIComponent* AI = (AIComponent*)em.get_component_of_entity(element->id, AIComponent::COMPONENT_TYPE); //change to player
		if (AI._state == AICOmponent::FIGHTING) {
			if (player.x > (xy.x - (range / 2)) && player.y < (xy.y + (range / 2))) {
				texture.animate(fight);
				player.health = -damage;
			}
		}
	}*/
}