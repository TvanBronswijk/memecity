#pragma once
#include "../memecity.engine.ecs/Component.h"

struct stats_component: public Component
{

private:
	int strength = 0;
	int perception = 0;
	int endurance = 0;
	int charisma = 0;
	int intelligence = 0;
	int agility = 0;
	int luck = 0;
public:
	stats_component(Entity* e);
	~stats_component();
};

