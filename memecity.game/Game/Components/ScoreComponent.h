#ifndef _SCORE_COMPONENT_H
#define _SCORE_COMPONENT_H
#include <ECS.h>
#include "Engine/Serialize.h"

struct ScoreComponent : public memecity::engine::ecs::Component, memecity::engine::serialization::Serializable
{
	int score;
	ScoreComponent(memecity::engine::ecs::Entity& entity)
		: ScoreComponent(entity, 35) {}

	ScoreComponent(memecity::engine::ecs::Entity& entity, int score)
		: memecity::engine::ecs::Component(entity), score(score) {};

	memecity::engine::serialization::SerializeInfo to_map() const override
	{
		std::map<std::string, std::any> map;

		map["score"] = this->score;

		return map;
	}

	std::map<std::string, std::string> test() const
	{
		std::map<std::string, std::string> map;

		map["score"] = std::to_string(this->score);

		return map;
	}

	void from_map(memecity::engine::serialization::SerializeInfo map) override
	{
		this->score = std::any_cast<int>(map["score"]);
	}
};



#endif
