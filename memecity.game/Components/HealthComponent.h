#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include <ECS.h>
#include <Engine\MultimediaManager.h>
#include "StatsComponent.h"
#include "DrawableComponent.h"

struct HealthComponent : public memecity::engine::ecs::Component{

public:
	size_t maxhealth;
	size_t health;
	std::unique_ptr<memecity::engine::texture::Texture> texture;

	HealthComponent(const memecity::engine::ecs::Entity& entity, memecity::engine::MultimediaManager& multimedia_manager) : memecity::engine::ecs::Component(entity) 
	{ calculate_health(); set_texture(multimedia_manager);  };

	memecity::engine::texture::Texture& get_texture()
	{
		return *texture;
	}

	void calculate_health() {
		auto stats = entity.get<StatsComponent>();
		maxhealth = ((stats->strength * 5) + (stats->endurance * 3) + (stats->agility * 2) + 50);
		health = maxhealth;
	}

	void set_texture(memecity::engine::MultimediaManager& multimedia_manager) {
		auto parent = entity.get<DrawableComponent>();
		std::string hp = "HP: ";
		hp += std::to_string(health);
		hp += "/";
		hp += std::to_string(maxhealth);

		auto npc_health_texture = multimedia_manager.get_text_texture(hp, "Minecraftia-Regular.ttf", 10, { 34,139,34 });
		npc_health_texture->set_position({ 0, -20 });
		npc_health_texture->set_parent(&parent->get_texture());
		texture = std::move(npc_health_texture);
	}
};

#endif
