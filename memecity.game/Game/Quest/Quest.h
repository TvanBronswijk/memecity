#ifndef _QUEST_H
#define  _QUEST_H
#include <queue>
#include <deque>
#include "Task.h"
#include <string>

struct Quest {
	std::string description;
	bool completed = false;

	std::queue<Task> _tasks;

	Quest(std::string description, std::deque<Task> tasks) :  description(description), _tasks(tasks){};
};

#endif;
