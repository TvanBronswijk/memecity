#pragma once
#include "../memecity.engine.ecs/Component.h"
#include <string>

struct StatsComponent: public Component
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

	StatsComponent(Entity* e);
	~StatsComponent();
	std::string get_type() override;
};

