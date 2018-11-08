#include"InteractionComponent.h"

ecs::component_typetoken InteractionComponent::COMPONENT_TYPE = "InteractionComponent";

std::map<std::string, std::any> InteractionComponent::to_map()
{
	std::map<std::string, std::any> map;

	map["smallTalk"] = this->_smallTalk;

	return map;
}

void InteractionComponent::from_map(std::map<std::string, std::any> map)
{
	//this->_smallTalk = std::any_cast</*TODO vector*/>(map["smallTalk"]);
}