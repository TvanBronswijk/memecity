#ifndef _STORYCOMPONENT_H
#define  _STORYCOMPONENT_H
#include <ECS.h>
#include <vector>
#include <algorithm> // copy
#include "QuestComponent.h"

struct StoryComponent : public memecity::engine::ecs::Component
{
	std::string description;
	bool active = false;

	std::vector<QuestComponent*> _quests;

	StoryComponent(memecity::engine::ecs::Entity& entity,std::string description, std::vector<QuestComponent*> quests) : memecity::engine::ecs::Component(entity),description(description), _quests(quests) {	};
};

#endif;
