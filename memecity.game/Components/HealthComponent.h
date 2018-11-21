#ifndef _HEALTHCOMPONENT_H
#define  _HEALTHCOMPONENT_H
#include <ECS.h>
#include <Engine\MultimediaManager.h>
#include "StatsComponent.h"
#include "DrawableComponent.h"

struct HealthComponent : public memecity::engine::ecs::Component{
public:
	int maxhealth;
	int health;

	std::unique_ptr<memecity::engine::texture::Texture> texture;

	HealthComponent(const memecity::engine::ecs::Entity& entity)
		: HealthComponent(entity, nullptr) {}
	HealthComponent(const memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::Texture> texture)
		: memecity::engine::ecs::Component(entity), texture(std::move(texture)) {}

	memecity::engine::texture::Texture& get_texture()
	{
		return *texture;
	}
};

#endif
