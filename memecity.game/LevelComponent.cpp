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
	_level = (rand() % world + (world-range) + (world - range));
}

std::string LevelComponent::get_type() {
	return "HealthComponent";
}