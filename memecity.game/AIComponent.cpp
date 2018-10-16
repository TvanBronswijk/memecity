#include"AIComponent.h"

std::string AIComponent::COMPONENT_TYPE = "AIComponent";

AIComponent::AIComponent(Entity* e) : Component(e) {
	this->entity_id = e->id;
	_fleeing = false;
	_fighting = true;
}

AIComponent::AIComponent(bool fighting, bool fleeing, Entity* e) : Component(e) {
	this->entity_id = e->id;
	_fleeing = fleeing;
	_fighting = fighting;
}

std::string AIComponent::get_type() {
	return COMPONENT_TYPE;
}