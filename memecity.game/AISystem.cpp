#include "AISystem.h"


std::string AISystem::COMPONENT_TYPE = "AISystem";

int RandomX(VelocityComponent* velocity) {
	return velocity->x = (rand() % (2 - -1)) + -1;
}

int RandomY(VelocityComponent* velocity) {
	return velocity->y = (rand() % (2 - -1)) + -1;
}

AISystem::AISystem(){
}

bool AISystem::is_on_event(Event *e) {
	return false;
}


std::string AISystem::get_type() {
	return COMPONENT_TYPE;
}
void AISystem::run(EntityManager &em) {
	auto vector = em.get_entities_with_component("AIComponent");

	for (auto & element : vector) {
		VelocityComponent* velocity = (VelocityComponent*)em.get_component_of_entity(element->id, "VelocityComponent");
		PositionComponent* xy = (PositionComponent*)em.get_component_of_entity(element->id, "PositionComponent");
	
		velocity->x += RandomX(velocity);
		velocity->y += RandomY(velocity);

		xy->x_position += velocity->x;
		xy->y_position += velocity->y;


		std::cout << "NPC has Placed with X: " << xy->x_position << "Y: " << xy->y_position << std::endl;
	}
}
void AISystem::run(EntityManager &em, Event *e) {

}