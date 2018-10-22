#include"HealthComponent.h"


std::string HealthComponent::COMPONENT_TYPE = "HealthComponent";

HealthComponent::HealthComponent(Entity* e) : Component(e) {
	this->entity_id = e->id;
	_health = 0;
}

HealthComponent::HealthComponent(int health, Entity* e) : Component(e) {
	this->entity_id = e->id;
	_health = health;
}

std::string HealthComponent::get_type() {
	return "HealthComponent";
}

std::map<std::string, AnyExtension> HealthComponent::to_map()
{
	std::map<std::string, AnyExtension> map;

	map["health"] = this->_health;

	nlohmann::json j = nlohmann::json(map);

	std::cout << j.dump() << std::endl;

	return map;
}

void HealthComponent::from_map(std::map<std::string, AnyExtension> map)
{
	this->_health = std::any_cast<int>(map["health"]);
}