#ifndef _LEVELCOMPONENT_H
#define  _LEVELCOMPONENT_H
#include <ECS.h>
#include <iostream>

struct LevelComponent : public memecity::engine::ecs::Component{

public:
	int level;

	LevelComponent(memecity::engine::ecs::Entity& entity) : LevelComponent(entity, 1) {};
	LevelComponent(memecity::engine::ecs::Entity& entity, int level) : memecity::engine::ecs::Component(entity), level(level) {};
};

#endif

