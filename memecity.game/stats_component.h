#pragma once
#include "../memecity.engine.ecs/Component.h"
#include <string>

struct stats_component: public Component
{
	static std::string COMPONENT_TYPE;

public:
	int strength = 0;
	int perception = 0;
	int endurance = 0;
	int charisma = 0;
	int intelligence = 0;
	int agility = 0;
	int luck = 0;

	stats_component(Entity* e);
	~stats_component();
	std::string get_type() override;
};

