#ifndef _SCORE_COMPONENT_H
#define _SCORE_COMPONENT_H

#include <ECS.h>
#include "Engine/Serialize.h"

struct ScoreComponent : memecity::engine::ecs::Component, memecity::engine::serialization::Serializable
{
	int score;
	
	ScoreComponent(memecity::engine::ecs::Entity& entity)
		: ScoreComponent(entity, 0) {}

	ScoreComponent(memecity::engine::ecs::Entity& entity, const int score) 
		: Component(entity), score(score) {};

	memecity::engine::serialization::SerializeInfo to_map() const override
	{
		memecity::engine::serialization::SerializeInfo map;
		map["score"] = std::to_string(this->score);
		return map;
	}

	void from_map(memecity::engine::serialization::SerializeInfo map) override
	{
		this->score = std::stoi(map["score"]);
	}
};

#endif