#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "Serializable.h"
#include <iostream>
#include <map>

struct HealthComponent : public Component, public Serializable {

	static std::string COMPONENT_TYPE;

public:
	int _health;
	HealthComponent(Entity* e);
	HealthComponent(int health, Entity* e);
	std::string get_type() override;
	std::map<std::string, std::any> to_map() override;
	void from_map(std::map<std::string, std::any> map) override;
};

#endif