#ifndef _PLAYER_COMPONENT_H
#define _PLAYER_COMPONENT_H

#include <ECS.h>
#include "../Quest/Story.h"
#include "Engine/Serialize.h"

struct PlayerComponent : memecity::engine::ecs::Component, public memecity::engine::serialization::Serializable
{
	std::vector<Story> _stories;

	int min_movement_speed, blik_coins;
	PlayerComponent(memecity::engine::ecs::Entity& entity, std::vector<Story> stories) : memecity::engine::ecs::Component(entity), _stories(stories), blik_coins(0), min_movement_speed(180) {};

	memecity::engine::serialization::SerializeInfo to_map() const override
	{
		memecity::engine::serialization::SerializeInfo map;
		map["PlayerComponent:blik_coins"] = std::to_string(this->blik_coins);
		return map;
	}

	void from_pair(std::pair<std::string, std::string> pair) override
	{
		const auto key = pair.first;
		if (key == "blik_coins")
		{
			this->blik_coins = std::stoi(pair.second);
		}
	}

};

#endif;