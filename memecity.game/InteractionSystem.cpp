#include "InteractionSystem.h"


std::string InteractionSystem::SYSTEM_TYPE = "InteractionSystem";

InteractionSystem::InteractionSystem() {
}

bool InteractionSystem::is_on_event(Event *e) {
	return false;
}


std::string InteractionSystem::get_type() {
	return SYSTEM_TYPE;
}
void InteractionSystem::run(EntityManager &em) {

}
void InteractionSystem::run(EntityManager &em, Event *e) {
	// fire off a random smalltalk or a custom message ;
}