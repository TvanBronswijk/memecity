#ifndef _PLAYERCOMPONENT_H
#define  _PLAYERCOMPONENT_H
#include <ECS.h>

struct PlayerComponent : public ecs::Component
{
	PlayerComponent(const ecs::Entity& entity) : ecs::Component(entity) {};
};

#endif;
