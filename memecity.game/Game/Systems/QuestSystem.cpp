#include "QuestSystem.h"
#include <ECS.h>
#include "../Components/PlayerComponent.h"
#include "../Components/StoryComponent.h"
#include "../Components/HealthComponent.h"
#include "..\Components\AIComponent.h"
#include "../Components/InteractionComponent.h"
#include "../Enum/QuestStates.h"
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
	if (task->counter >= task->amount) {
		task->completed = true;
		if (task->target != NULL) {
			auto interaction = task->target->get<InteractionComponent>();
			if (interaction != nullptr) {
				interaction->text.clear();
				interaction->text.emplace_back(" ");
			}
		}
		return true;
	}
	if (task->target != NULL) {
		auto interaction = task->target->get<InteractionComponent>();
		if (interaction != nullptr) {
			if (interaction->text[0] == " ") {
				interaction->text = task->dialog;
			}
		}
	}
	return false;
}

void QuestSystem::on_event(EntityManager &em, QuestEventArgs args) {
	auto player_component = em.get_components_of_type<PlayerComponent>()[0];
	auto stories = player_component.get()._stories;

	for (auto it = stories.begin(); it != stories.end(); ++it) {
		auto story = (*it)->get<StoryComponent>();
		if (story->active) {
			if (!story->_quests.empty()) {
				switch (story->_quests.front()->_tasks.front()->state) {
				case Quest_State::Dropping:
					check_task_dropping(args, story->_quests.front()->_tasks.front());
					break;
				case Quest_State::Fighting:
					check_task_fighting(args, story->_quests.front()->_tasks.front());
					break;
				case Quest_State::Finding:
					check_task_finding(args, story->_quests.front()->_tasks.front());
					break;
				case Quest_State::Interaction:
					check_task_interaction(args, story->_quests.front()->_tasks.front());
					break;
				}
			}
		}
	}
}

void QuestSystem::check_task_interaction(QuestEventArgs args, TaskComponent* task) {
	if (task->target == args.target) {
		auto interaction_target = args.target->get<InteractionComponent>();
		if (interaction_target->current_text_int == interaction_target->text.size()-1){
			task->counter++;
			interaction_target->current_text_int = 0;
		}
	}
}
void QuestSystem::check_task_finding(QuestEventArgs args, TaskComponent* task) {
	if (task->item == args.item) {
		task->counter++;
	}
}
void QuestSystem::check_task_dropping(QuestEventArgs args, TaskComponent* task) {
	if (task->item == args.item) {
		task->counter++;
	}
}
void QuestSystem::check_task_fighting(QuestEventArgs args, TaskComponent* task) {
	if (args.target->get<AIComponent>() != nullptr) {
		if (task->target->get<AIComponent>()->name == args.target->get<AIComponent>()->name) {
			if (args.target->get<HealthComponent>()->health <= 0) {
				if (task->item == args.item) {
					task->counter++;
				}
			}
		}
	}
}