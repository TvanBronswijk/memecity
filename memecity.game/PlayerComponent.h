#ifndef _PLAYERCOMPONENT_H
#define  _PLAYERCOMPONENT_H
#include "../memecity.engine.ecs/Component.h"

struct PlayerComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	PlayerComponent(ecs::Entity* e) : ecs::Component(e) {};
	ecs::component_typetoken get_type_token() override { return PlayerComponent::COMPONENT_TYPE; }
};

#endif;