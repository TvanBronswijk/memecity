#ifndef _ANIMATION_COMPONENT_H
#define _ANIMATION_COMPONENT_H

#include "../memecity.engine.ecs/Component.h"
#include "AnimatedTexture.h"

struct AnimationComponent : public Component
{
	static std::string COMPONENT_TYPE;
	bool is_fighting = false;

	std::string get_type() override;
	AnimationComponent(Entity* entity) : Component(entity){}
};

#endif