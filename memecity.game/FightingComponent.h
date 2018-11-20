#ifndef _FIGHTINGCOMPONENT_H
#define  _FIGHTINGCOMPONENT_H
#include <ECS.h>
#include <vector>

struct FightingComponent : public memecity::engine::ecs::Component {

public:
	std::unique_ptr<memecity::engine::texture::Texture> texture;

	FightingComponent(const memecity::engine::ecs::Entity& entity, std::unique_ptr<memecity::engine::texture::Texture> texture) : memecity::engine::ecs::Component(entity), texture(std::move(texture)) {};

	memecity::engine::texture::Texture& get_texture()
	{
		return *texture;
	}
};

#endif
