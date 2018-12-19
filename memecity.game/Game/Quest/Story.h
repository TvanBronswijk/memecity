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

	int blik_coins;
	int exp;

	std::queue<Quest> quests;

	Story(std::string description,int exp, int blik_coins,std::deque<Quest> quests) : description(description), quests(quests), completed(false),active(true), blik_coins(blik_coins), exp(exp) {};
};

#endif;
