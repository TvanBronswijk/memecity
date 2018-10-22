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

std::map<std::string, AnyExtension> InteractionComponent::to_map()
{
	std::map<std::string, AnyExtension> map;

	map["smallTalk"] = this->_smallTalk;

	nlohmann::json j = nlohmann::json(map);

	std::cout << j.dump() << std::endl;

	return map;
}

void InteractionComponent::from_map(std::map<std::string, AnyExtension> map)
{
	this->_smallTalk = std::any_cast</*TODO vector*/>(map["smallTalk"]);
}