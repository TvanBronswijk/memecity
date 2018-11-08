#include"HealthComponent.h"

ecs::component_typetoken HealthComponent::COMPONENT_TYPE = "HealthComponent";


std::map<std::string, std::any> HealthComponent::to_map()
{
	std::map<std::string, std::any> map;

	map["health"] = this->_health;

	return map;
}

void HealthComponent::from_map(std::map<std::string, std::any> map)
{
	this->_health = std::any_cast<int>(map["health"]);
}