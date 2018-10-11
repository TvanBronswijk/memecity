#include "AISystem.h"

int RandomX() {
	return rand() % -2 + 2;
}

int RandomY() {
	return rand() % -2 + 2;
}

AISystem::AISystem() {
	EntityManager em;
	Entity *npc = em.create_entity();
	AIComponent AI(npc);
	PositionComponent PC(npc);
	VelocityComponent VC(npc);
	em.register_component(&AI);
	em.register_component(&PC);
	em.register_component(&VC);
	em.register_system(this);
}

std::string AISystem::get_type() {
	return "AISystem";
}
void AISystem::run(EntityManager &em) {
	auto vector = em.get_components_of_type("AIComponent");

	for (auto & element : vector) {
		auto vector2 = em.get_components_of_entity(element->entity_id);

	}

	PC.x_position = PC.x_position + RandomX();
	PC.y_position = PC.y_position + RandomY();


}
void AISystem::run(EntityManager &em, Event *e) {

}