#ifndef _PLAYERCOMPONENT_H
#define  _PLAYERCOMPONENT_H
#include <ECS.h>
#include <algorithm> // copy
#include "../Quest/Story.h"

struct PlayerComponent : public memecity::engine::ecs::Component
{
	std::vector<Story> _stories;


	PlayerComponent(memecity::engine::ecs::Entity& entity, std::vector<Story> stories) : memecity::engine::ecs::Component(entity), _stories(stories) {};
};

#endif;
