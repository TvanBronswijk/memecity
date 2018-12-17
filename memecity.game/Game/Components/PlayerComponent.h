#ifndef _PLAYER_COMPONENT_H
#define _PLAYER_COMPONENT_H

#include <ECS.h>

struct PlayerComponent : memecity::engine::ecs::Component
{
	int blik_coins;
	PlayerComponent(memecity::engine::ecs::Entity& entity) : memecity::engine::ecs::Component(entity),blik_coins(0) {};
};

#endif;