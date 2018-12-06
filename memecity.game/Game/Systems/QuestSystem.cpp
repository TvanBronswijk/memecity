#include "QuestSystem.h"
#include <ECS.h>
#include "../Components/PlayerComponent.h"
#include "../Components/StoryComponent.h"
#include "../Components/InteractionComponent.h"
#include <vector>
#include <algorithm> 
#include <iostream>

using namespace memecity::engine::ecs;


void QuestSystem::run(EntityManager &em) const {
	auto player_component = em.get_components_of_type<PlayerComponent>()[0];
	auto stories = player_component.get()._stories;

	//std::for_each(stories.begin(), stories.end(), [&](auto s) {story(s);});

	for (auto it = stories.begin(); it != stories.end(); ++it) {
		story(*it);
	}
}

void QuestSystem::story(const Entity* story_entity) const {
	auto story = story_entity->get<StoryComponent>();
	if (story->active) {
		if (story->_quests.empty()) {
			if (story->completed) return;
			story->completed = true;
		}
		else {
			if (quest(story->_quests.front())) {
				story->_quests.pop();
			}
		}
	}
}

bool QuestSystem::quest(QuestComponent* quest) const{
	if (quest->_tasks.empty()) {
		quest->completed = true;
		return true;
	}
	else {
		if (task(quest->_tasks.front())) {
			quest->_tasks.pop();
		}
	}
	return false;
}

bool QuestSystem::task(TaskComponent* task) const {
	auto interaction = task->target->get<InteractionComponent>();
	if (task->counter >= task->amount) {
		task->completed = true;
		if (interaction != nullptr) {
			interaction->text.clear();
			interaction->text.emplace_back(" ");
		}
		return true;
	}
	if (interaction != nullptr) {
		if (interaction->text[0] == " ") {
			interaction->text = task->dialog;
		}
	}
	return false;
}

