#ifndef _LEVELCOMPONENT_H
#define  _LEVELCOMPONENT_H
#include <ECS.h>
#include <iostream>

struct LevelComponent : public ecs::Component{

public:
	int level;

	LevelComponent(const ecs::Entity& entity) : LevelComponent(entity, 1) {};
	LevelComponent(const ecs::Entity& entity, int level) : ecs::Component(entity), level(level) {};
	LevelComponent(const ecs::Entity& entity, int world, int range) : ecs::Component(entity), level((rand() % (world - (range / 2))/*min*/ + (world + (range / 2)))/*max*/) {};
};

#endif

