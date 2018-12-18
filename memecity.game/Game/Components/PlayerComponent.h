﻿#ifndef _PLAYERCOMPONENT_H
#define  _PLAYERCOMPONENT_H
#include <ECS.h>
#include "../Quest/Story.h"

struct PlayerComponent : public memecity::engine::ecs::Component
{
	std::vector<Story> _stories;

	int min_movement_speed;
	int blik_coins;
	PlayerComponent(memecity::engine::ecs::Entity& entity, std::vector<Story> stories) : memecity::engine::ecs::Component(entity), _stories(stories), blik_coins(0), min_movement_speed(180) {};
};

#endif;
