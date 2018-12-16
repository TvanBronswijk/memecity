#ifndef _PLAYER_COMPONENT_H
#define _PLAYER_COMPONENT_H

#include <ECS.h>

struct PlayerComponent : memecity::engine::ecs::Component
{
	PlayerComponent(memecity::engine::ecs::Entity& entity) 
		: Component(entity) {}
};

#endif;