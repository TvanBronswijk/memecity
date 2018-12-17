#ifndef _STATS_COMPONENT_H
#define _STATS_COMPONENT_H

#include <ECS.h>
#include "Engine/Serialization/Serializable.h"

struct StatsComponent: memecity::engine::ecs::Component, memecity::engine::serialization::Serializable
{
	int strength, perception, endurance, charisma, intelligence, agility, luck;

	StatsComponent(memecity::engine::ecs::Entity& entity) : StatsComponent(entity, 0, 0, 0, 0, 0, 0, 0) {};
	StatsComponent(memecity::engine::ecs::Entity& entity, const int strength, const int perception, const int endurance, const int charisma, const int intelligence, const int agility, const int luck) 
		: Component(entity), strength(strength), perception(perception), endurance(endurance), charisma(charisma), intelligence(intelligence), agility(agility), luck(luck) {};

	memecity::engine::serialization::SerializeInfo to_map() const override
	{
		memecity::engine::serialization::SerializeInfo map;
		map["strength"] = std::to_string(this->strength);
		map["perception"] = std::to_string(this->perception);
		map["endurance"] = std::to_string(this->endurance);
		map["charisma"] = std::to_string(this->charisma);
		map["intelligence"] = std::to_string(this->intelligence);
		map["agility"] = std::to_string(this->agility);
		map["luck"] = std::to_string(this->luck);
		return map;
	}

	void from_map(memecity::engine::serialization::SerializeInfo map) override
	{
		this->strength = std::any_cast<int>(map["strength"]);
		this->perception = std::any_cast<int>(map["perception"]);
		this->endurance = std::any_cast<int>(map["endurance"]);
		this->charisma = std::any_cast<int>(map["charisma"]);
		this->intelligence = std::any_cast<int>(map["intelligence"]);
		this->agility = std::any_cast<int>(map["agility"]);
		this->luck = std::any_cast<int>(map["luck"]);
	}
};

#endif
