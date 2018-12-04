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

	std::unique_ptr<memecity::engine::texture::TextTexture> texture;

	HealthComponent(memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::TextTexture> texture)
		: HealthComponent(entity,0, std::move(texture)) {}
	HealthComponent(memecity::engine::ecs::Entity& entity,int health, std::unique_ptr<memecity::engine::texture::TextTexture> texture)
		: memecity::engine::ecs::Component(entity), maxhealth(health),health(health), texture(std::move(texture)) {}

	memecity::engine::texture::TextTexture& get_texture()
	{
		return *texture;
	}
};

#endif
