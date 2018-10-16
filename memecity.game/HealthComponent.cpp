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