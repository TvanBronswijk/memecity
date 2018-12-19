#ifndef _EXP_COMPONENT_H
#define _EXP_COMPONENT_H

#include "Engine/Serialize.h"
#include <ECS.h>

struct ExpComponent : public memecity::engine::ecs::Component, public memecity::engine::serialization::Serializable
{
	int exp, next_level, total_exp;
	ExpComponent(memecity::engine::ecs::Entity& entity)
		: ExpComponent(entity, 0, 0) {};
	ExpComponent(memecity::engine::ecs::Entity& entity, int exp, int next_level)
		: memecity::engine::ecs::Component(entity), exp(exp), next_level(next_level) {};

	memecity::engine::serialization::SerializeInfo to_map() const override
	{
		memecity::engine::serialization::SerializeInfo map;
		map["ExpComponent:exp"] = std::to_string(this->exp);
		map["ExpComponent:next_level"] = std::to_string(this->next_level);
		map["ExpComponent:total_exp"] = std::to_string(this->total_exp);
		return map;
	}

	void from_pair(std::pair<std::string, std::string> pair) override
	{
		const auto key = pair.first;
		if (key == "exp")
		{
			this->exp = std::stoi(pair.second);
			return;
		}
		if (key == "next_level")
		{
			this->next_level = std::stoi(pair.second);
			return;
		}
		if (key == "total_exp")
		{
			this->total_exp = std::stoi(pair.second);
		}
	}
};

#endif
