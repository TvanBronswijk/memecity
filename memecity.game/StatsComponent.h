#ifndef _STATS_COMPONENT_H
#define _STATS_COMPONENT_H
#include "../memecity.engine.ecs/Component.h"
#include <string>

struct StatsComponent: public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	int strength, perception, endurance, charisma, intelligence, agility, luck;
	StatsComponent(ecs::Entity* e) : ecs::Component(e) {};
	ecs::component_typetoken get_type_token() override { return StatsComponent::COMPONENT_TYPE; }
};

#endif