#ifndef _STATS_COMPONENT_H
#define _STATS_COMPONENT_H
#include <ECS.h>
#include <string>

struct StatsComponent: public ecs::Component
{
	int strength, perception, endurance, charisma, intelligence, agility, luck;
	StatsComponent(const ecs::Entity& entity) : StatsComponent(entity, 0, 0, 0, 0, 0, 0, 0) {};
	StatsComponent(const ecs::Entity& entity, int strength, int perception, int endurance, int charisma, int intelligence, int agility, int luck) 
		: ecs::Component(entity), strength(strength), perception(perception), endurance(endurance), charisma(charisma), intelligence(intelligence), agility(agility), luck(luck) {};
};

#endif
