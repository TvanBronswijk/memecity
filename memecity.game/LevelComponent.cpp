#include"LevelComponent.h"


std::string LevelComponent::COMPONENT_TYPE = "LevelComponent";

LevelComponent::LevelComponent(Entity* e) : Component(e) {
	this->entity_id = e->id;
	_level = 0;
}

LevelComponent::LevelComponent(int level, Entity* e) : Component(e) {
	this->entity_id = e->id;
	_level = level;
}

LevelComponent::LevelComponent(int world, int range, Entity* e) : Component(e) {
	this->entity_id = e->id;
	_level = (rand() % (world-(range/2))/*min*/ + (world +(range/2)))/*max*/;
}

std::string LevelComponent::get_type() {
	return "levelComponent";
}

std::map<std::string, AnyExtension> LevelComponent::to_map()
{
	std::map<std::string, AnyExtension> map;

	map["level"] = this->_level;

	nlohmann::json j = nlohmann::json(map);

	std::cout << j.dump() << std::endl;

	return map;
}

void LevelComponent::from_map(std::map<std::string, AnyExtension> map)
{
	this->_level = std::any_cast<int>(map["level"]);
}