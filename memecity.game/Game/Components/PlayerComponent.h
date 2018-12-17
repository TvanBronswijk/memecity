#ifndef _PLAYER_COMPONENT_H
#define _PLAYER_COMPONENT_H

#include <ECS.h>

struct PlayerComponent : memecity::engine::ecs::Component
{
	int BlikCoins;
	PlayerComponent(memecity::engine::ecs::Entity& entity) : memecity::engine::ecs::Component(entity),BlikCoins(0) {};
};

#endif;