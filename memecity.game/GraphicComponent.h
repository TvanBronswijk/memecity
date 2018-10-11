#ifndef _GRAPHICSCOMPONENT_H
#define _GRAPHICSCOMPONENT_H

#include <memory>
#include "Texture.h"
#include "../memecity.engine.ecs/Component.h"

struct GraphicComponent : public Component
{

public:
	GraphicComponent(std::weak_ptr<Texture> texture);
	std::string get_type() override;
	std::weak_ptr<Texture> texture;

};

#endif

