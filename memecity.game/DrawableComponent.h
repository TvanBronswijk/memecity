#ifndef _DRAWABLECOMPONENT_H
#define _DRAWABLECOMPONENT_H

#include "Texture.h"
#include "../memecity.engine.ecs/Component.h"

struct DrawableComponent : public Component
{
	static std::string COMPONENT_TYPE;

public:
	std::string get_type() override;
	std::shared_ptr<Texture>  texture;
	DrawableComponent(Entity* entity) : Component(entity){};
};

#endif

