#ifndef _STORY_H
#define  _STORY_H
#include <queue>
#include <deque>
#include <string>
#include "Quest.h"

struct Story
{
	bool completed;
	std::string description;
	bool active;

	std::queue<Quest> quests;

	Story(std::string description,std::deque<Quest> quests) : description(description), quests(quests), completed(false),active(true) {};
};

#endif;