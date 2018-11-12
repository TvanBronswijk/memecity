#ifndef _LEVELCOMPONENT_H
#define  _LEVELCOMPONENT_H
#include <ECS.h>
#include <iostream>

struct LevelComponent : public memecity::engine::ecs::Component{

public:
	int level;

	LevelComponent(const memecity::engine::ecs::Entity& entity) : LevelComponent(entity, 1) {};
	LevelComponent(const memecity::engine::ecs::Entity& entity, int level) : memecity::engine::ecs::Component(entity), level(level) {};
	LevelComponent(const memecity::engine::ecs::Entity& entity, int world, int range) : memecity::engine::ecs::Component(entity), level((rand() % (world - (range / 2))/*min*/ + (world + (range / 2)))/*max*/) {};
};

#endif

