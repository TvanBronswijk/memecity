#ifndef _STORYCOMPONENT_H
#define  _STORYCOMPONENT_H
#include <ECS.h>
#include <queue>
#include <deque>
#include <algorithm> // copy
#include "QuestComponent.h"

struct StoryComponent : public memecity::engine::ecs::Component
{
	bool completed = false;
	std::string description;
	bool active = true;

	std::queue<QuestComponent*> _quests;

	StoryComponent(memecity::engine::ecs::Entity& entity,std::string description,std::deque<QuestComponent*> quests) : memecity::engine::ecs::Component(entity),description(description), _quests(quests) {};
};

#endif;
