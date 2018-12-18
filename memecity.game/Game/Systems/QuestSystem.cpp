#include "QuestSystem.h"
#include <ECS.h>
#include "../Components/PlayerComponent.h"
#include "../Quest/Story.h"
#include "../Quest/Task.h"
#include "../Quest/Quest.h"
#include "../Components/HealthComponent.h"
#include "../Components/ItemComponent.h"
#include "../Components/AIComponent.h"
#include "../Components/InteractionComponent.h"
#include "../Enum/QuestStates.h"
#include <vector>
#include <algorithm> 
#include <iostream>

using namespace memecity::engine::ecs;


void QuestSystem::run(EntityManager &em, float dt) const {
	auto player_component = em.get_components_of_type<PlayerComponent>()[0];
	auto& stories = player_component.get()._stories;

	for (auto it = stories.begin(); it != stories.end(); ++it) {
		story(*it);
	}
}

void QuestSystem::story(Story& story) const {
	if (story.active) {
		if (story.quests.empty()) {
			if (story.completed) return;
			story.completed = true;
		}
		else {
			if (quest(story.quests.front())) {
				story.quests.pop();
			}
		}
	}
}

bool QuestSystem::quest(Quest& quest) const{
	if (quest.tasks.empty()) {
		quest.completed = true;
		return true;
	}
	else {
		if (task(quest.tasks.front())) {
			quest.tasks.pop();
		}
	}
	return false;
}

bool QuestSystem::task(Task& task) const {
	if (task.counter >= task.amount) {
		task.completed = true;
		if (task.target != NULL) {
			auto interaction = task.target->get<InteractionComponent>();
			if (interaction != nullptr) {
				interaction->text.clear();
				interaction->text.emplace_back(" ");
			}
		}
		return true;
	}
	if (task.target != NULL) {
		auto interaction = task.target->get<InteractionComponent>();
		if (interaction != nullptr) {
			if (interaction->text[0] == " ") {
				interaction->text = task.dialog;
			}
		}
	}
	return false;
}

void QuestSystem::on_event(EntityManager &em, QuestEventArgs args) {
	auto player_component = em.get_components_of_type<PlayerComponent>()[0];
	auto& stories = player_component.get()._stories;

	for (auto it = stories.begin(); it != stories.end(); ++it) {
		auto& story = *it;
		if (story.active) {
			if (!story.quests.empty()) {
				auto &task = story.quests.front().tasks.front();
				switch (task.state) {
				case Quest_State::Dropping:
					check_task_dropping(args, task);
					break;
				case Quest_State::Fighting:
					check_task_fighting(args, task);
					break;
				case Quest_State::Finding:
					check_task_finding(args, task);
					break;
				case Quest_State::Interaction:
					check_task_interaction(args, task);
					break;
				}
			}
		}
	}
}

void QuestSystem::check_task_interaction(QuestEventArgs args, Task& task) {
	if (task.target == args.target) {
		auto interaction_target = args.target->get<InteractionComponent>();
		if (interaction_target->current_text_int == interaction_target->text.size()-1){
			task.counter++;
			interaction_target->current_text_int = 0;
		}
	}
}
void QuestSystem::check_task_finding(QuestEventArgs args, Task& task) {
	auto item = args.target->get<ItemComponent>();
	if(item != nullptr){
		if (task.target->get<ItemComponent>()->name == item->name) {
			task.counter++;
		}
	}
}
void QuestSystem::check_task_dropping(QuestEventArgs args, Task& task) {
	if (task.item == args.item) {
		//TODO: implement quest_drop
		task.counter++;
	}
}
void QuestSystem::check_task_fighting(QuestEventArgs args, Task& task) {
	if (args.target->get<AIComponent>() != nullptr) {
		if (task.target->get<AIComponent>()->name == args.target->get<AIComponent>()->name) {
			if (args.target->get<HealthComponent>()->health <= 0) {
				if (task.item == args.item) {
					task.counter++;
				}
			}
		}
	}
}