#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "Serializable.h"
#include <iostream>
#include <map>

struct HealthComponent : public ecs::Component, public Serializable {


	static ecs::component_typetoken COMPONENT_TYPE;

public:
	int _health;
	HealthComponent(const ecs::Entity& entity) : ecs::Component(entity) {
		_health = 1;
	};
	HealthComponent(const ecs::Entity& entity, int health) : ecs::Component(entity) {
		_health = health;
	};
	ecs::component_typetoken get_type_token() const override { return HealthComponent::COMPONENT_TYPE; }
	std::map<std::string, std::any> to_map() override;
	void from_map(std::map<std::string, std::any> map) override;
};

#endif