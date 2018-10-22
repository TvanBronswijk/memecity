#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include "SerializableClass.h"
#include <iostream>
#include <map>

struct HealthComponent : public Component, public SerializableClass {

	static std::string COMPONENT_TYPE;

public:
	int _health;
	HealthComponent(Entity* e);
	HealthComponent(int health, Entity* e);
	std::string get_type() override;
	std::map<std::string, AnyExtension> to_map() override;
	void from_map(std::map<std::string, AnyExtension> map) override;
};

#endif