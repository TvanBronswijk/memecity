#include "AISystem.h"

int RandomX(VelocityComponent* velocity) {
	return velocity->x = rand() % -2 + 2;
}

int RandomY(VelocityComponent* velocity) {
	return velocity->y = rand() % -2 + 2;
}

AISystem::AISystem() {

}

std::string AISystem::get_type() {
	return "AISystem";
}
void AISystem::run(EntityManager &em) {
	auto vector = em.get_entities_with_component("AIComponent");

	for (auto & element : vector) {
		VelocityComponent* velocity = (VelocityComponent*)em.get_component_of_entity(element->id, "VelocityComponent");
	
		velocity->x += RandomX(velocity);
		velocity->y += RandomY(velocity);
	}
}
void AISystem::run(EntityManager &em, Event *e) {

}