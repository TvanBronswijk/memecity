#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include <ECS.h>
#include <Engine\MultimediaManager.h>
#include <Engine\Serialize.h>

struct HealthComponent : public memecity::engine::ecs::Component, memecity::engine::serialization::Serializable
{
public:
	int maxhealth, health;

	std::unique_ptr<memecity::engine::texture::TextTexture> texture;

	HealthComponent(memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::TextTexture> texture)
		: HealthComponent(entity, 0, std::move(texture)) {}
	HealthComponent(memecity::engine::ecs::Entity& entity, int health, std::unique_ptr<memecity::engine::texture::TextTexture> texture)
		: memecity::engine::ecs::Component(entity), maxhealth(health), health(health), texture(std::move(texture)) {}

	memecity::engine::texture::TextTexture& get_texture()
	{
		return *texture;
	}

	memecity::engine::serialization::SerializeInfo to_map() const override
	{
		memecity::engine::serialization::SerializeInfo map;
		map["HealthComponent:maxhealth"] = std::to_string(this->maxhealth);
		map["HealthComponent:health"] = std::to_string(this->health);
		return map;
	}

	void from_pair(std::pair<std::string, std::string> pair) override
	{
		const auto key = pair.first;
		if (key == "maxhealth")
		{
			this->maxhealth = std::stoi(pair.second);
		}
		else if (key == "health")
		{
			this->health = std::stoi(pair.second);
		}
	}
};

#endif
