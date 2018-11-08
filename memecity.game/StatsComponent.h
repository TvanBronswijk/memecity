#ifndef _STATS_COMPONENT_H
#define _STATS_COMPONENT_H
#include <ECS.h>
#include <string>

struct StatsComponent: public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	int strength, perception, endurance, charisma, intelligence, agility, luck;
	StatsComponent(const ecs::Entity& entity) : ecs::Component(entity) {};
	ecs::component_typetoken get_type_token() const override { return StatsComponent::COMPONENT_TYPE; }
};

#endif