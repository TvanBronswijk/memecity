#ifndef _QUESTCOMPONENT_H
#define  _QUESTCOMPONENT_H
#include <ECS.h>
#include <queue>
#include <deque>
#include <algorithm> // copy
#include "TaskComponent.h"

struct QuestComponent : public memecity::engine::ecs::Component
{
	std::string description;
	bool completed = false;

	std::queue<TaskComponent*> _tasks;

	QuestComponent(memecity::engine::ecs::Entity& entity, std::string description, std::deque<TaskComponent*> tasks) : memecity::engine::ecs::Component(entity), description(description), _tasks(tasks){	};
};

#endif;
