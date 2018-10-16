#include"InteractionComponent.h"


std::string InteractionComponent::COMPONENT_TYPE = "InteractionComponent";

InteractionComponent::InteractionComponent(Entity* e) : Component(e) {
	this->entity_id = e->id;
	_smallTalk = { "Hello Stranger!", "Sorry, i can't talk.", "what are you doing?" };
}

InteractionComponent::InteractionComponent(std::vector<std::string> smallTalk, Entity* e) : Component(e) {
	this->entity_id = e->id;
	_smallTalk = smallTalk;
}


std::string InteractionComponent::get_type() {
	return "InteractionComponent";
}