#include"AIComponent.h"

std::string AIComponent::COMPONENT_TYPE = "AIComponent";

AIComponent::AIComponent(Entity* e) : Component(e) {
	this->entity_id = e->id;
	this->_state = FIGHTING;
}

AIComponent::AIComponent(State state, Entity* e) : Component(e) {
	this->entity_id = e->id;
	this->_state = state;
}

std::string AIComponent::get_type() {
	return COMPONENT_TYPE;
}