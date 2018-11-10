#ifndef _DRAWABLECOMPONENT_H
#define _DRAWABLECOMPONENT_H
#include <ECS.h>
#include "Texture.h"

struct DrawableComponent : public ecs::Component
{
	std::shared_ptr<Texture> texture;
	DrawableComponent(const ecs::Entity& entity)
		: DrawableComponent(entity, nullptr) {};
	DrawableComponent(const ecs::Entity& entity, std::shared_ptr<Texture>  texture) 
		: ecs::Component(entity), texture(texture) {};

};

#endif

