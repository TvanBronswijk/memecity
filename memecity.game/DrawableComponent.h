#ifndef _DRAWABLECOMPONENT_H
#define _DRAWABLECOMPONENT_H
#include <ECS.h>
#include "Texture.h"

struct DrawableComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	std::unique_ptr<Texture>  texture;
	DrawableComponent(const ecs::Entity& entity) : ecs::Component(entity){};
	ecs::component_typetoken get_type_token() const override { return DrawableComponent::COMPONENT_TYPE; }
};

#endif

