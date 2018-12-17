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
		map["StatsComponent=strength"] = std::to_string(this->strength);
		map["StatsComponent=perception"] = std::to_string(this->perception);
		map["StatsComponent=endurance"] = std::to_string(this->endurance);
		map["StatsComponent=charisma"] = std::to_string(this->charisma);
		map["StatsComponent=intelligence"] = std::to_string(this->intelligence);
		map["StatsComponent=agility"] = std::to_string(this->agility);
		map["StatsComponent=luck"] = std::to_string(this->luck);
		return map;
	}

	void from_pair(const std::pair<std::string, std::string> pair) override
	{
		const auto key = pair.first;
		if (key == "strength")
		{
			this->strength = std::stoi(pair.second);
			return;
		}
		
		if (key == "perception")
		{
			this->perception = std::stoi(pair.second);
			return;
		}

		if (key == "endurance")
		{
			this->endurance = std::stoi(pair.second);
			return;
		}

		if (key == "charisma")
		{
			this->charisma = std::stoi(pair.second);
			return;
		}

		if (key == "intelligence")
		{
			this->intelligence = std::stoi(pair.second);
			return;
		}

		if (key == "agility")
		{
			this->agility = std::stoi(pair.second);
			return;
		}

		if (key == "luck")
		{
			this->luck = std::stoi(pair.second);
		}
	}
};

#endif
