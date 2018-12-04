#ifndef _QUESTCOMPONENT_H
#define  _QUESTCOMPONENT_H
#include <ECS.h>
#include <vector>
#include <algorithm> // copy
#include "TaskComponent.h"

struct QuestComponent : public memecity::engine::ecs::Component
{
	std::string description;
	bool completed = false;

	std::vector<TaskComponent*> _tasks;

	QuestComponent(memecity::engine::ecs::Entity& entity, std::string description, std::vector<TaskComponent*> tasks) : memecity::engine::ecs::Component(entity), description(description), _tasks(tasks){	};
};

#endif;
