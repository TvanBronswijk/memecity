#ifndef _PLAYERCOMPONENT_H
#define  _PLAYERCOMPONENT_H
#include <ECS.h>

struct PlayerComponent : public memecity::engine::ecs::Component
{
	int blik_coins;
	PlayerComponent(memecity::engine::ecs::Entity& entity) : memecity::engine::ecs::Component(entity),blik_coins(0) {};
};

#endif;
