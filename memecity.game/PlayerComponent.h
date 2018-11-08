#ifndef _PLAYERCOMPONENT_H
#define  _PLAYERCOMPONENT_H
#include <ECS.h>

struct PlayerComponent : public ecs::Component
{
	static ecs::component_typetoken COMPONENT_TYPE;
	PlayerComponent(const ecs::Entity& entity) : ecs::Component(entity) {};
	ecs::component_typetoken get_type_token() const override { return PlayerComponent::COMPONENT_TYPE; }
};

#endif;