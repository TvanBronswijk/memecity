#ifndef _DRAWABLECOMPONENT_H
#define _DRAWABLECOMPONENT_H
#include <ECS.h>
#include "Texture.h"

struct DrawableComponent : public ecs::Component
{
private:
	std::unique_ptr<Texture> texture;

public:
	DrawableComponent(const ecs::Entity& entity)
		: DrawableComponent(entity, nullptr) {}
	DrawableComponent(const ecs::Entity& entity, std::unique_ptr<Texture> texture)
		: ecs::Component(entity), texture(std::move(texture)){}
	Texture& get_texture()
	{
		return *texture;
	}
};

#endif

