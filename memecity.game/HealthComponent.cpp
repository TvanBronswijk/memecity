#include"HealthComponent.h"

HealthComponent::HealthComponent(Entity* e) : Component(e) {
	this->entity_id = e->id;
	_health = 0;
}

HealthComponent::HealthComponent(int health, Entity* e) : Component(e) {
	_health = health;
}

std::string HealthComponent::get_type() {
	return "HealthComponent";
}