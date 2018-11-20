#ifndef _STATS_COMPONENT_H
#define _STATS_COMPONENT_H
#include <ECS.h>
#include <string>
#include "LevelComponent.h"

struct StatsComponent: public memecity::engine::ecs::Component
{
	size_t strength, perception, endurance, charisma, intelligence, agility, luck;
	StatsComponent(const memecity::engine::ecs::Entity& entity) : StatsComponent(entity, 5, 5, 5, 5, 5, 5, 5) {};
	StatsComponent(const memecity::engine::ecs::Entity& entity, size_t strength, size_t perception, size_t endurance, size_t charisma, size_t intelligence, size_t agility, size_t luck)
		: memecity::engine::ecs::Component(entity), strength(strength), perception(perception), endurance(endurance), charisma(charisma), intelligence(intelligence), agility(agility), luck(luck) { calculate_stats(); };

	void calculate_stats() {
		auto levelcomponent = entity.get<LevelComponent>();
		size_t points = levelcomponent->level * 5;
		
		size_t strength_points = (rand() % points);
		strength += strength_points;
		points -= strength_points;
		size_t perception_points = (rand() % points);
		perception += perception_points;
		points -= perception_points;
		size_t endurance_points = (rand() % points);
		endurance += endurance_points;
		points -= endurance_points;
		size_t charisma_points = (rand() % points);
		charisma += charisma_points;
		points -= charisma_points;
		size_t intelligence_points = (rand() % points);
		intelligence += intelligence_points;
		points -= intelligence_points;
		size_t agility_points = (rand() % points);
		agility += agility_points;
		points -= agility_points;
		luck += points;
	}
};

#endif
