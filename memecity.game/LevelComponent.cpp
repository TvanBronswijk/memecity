#include"LevelComponent.h"

ecs::component_typetoken LevelComponent::COMPONENT_TYPE = "LevelComponent";


std::map<std::string, std::any> LevelComponent::to_map()
{
	std::map<std::string, std::any> map;

	map["level"] = this->_level;

	return map;
}

void LevelComponent::from_map(std::map<std::string, std::any> map)
{
	this->_level = std::any_cast<int>(map["level"]);
}