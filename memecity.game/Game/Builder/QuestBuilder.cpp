#include "QuestBuilder.h"
#include "../Generate.h"

using namespace memecity::engine::ecs;

std::vector<StoryComponent*> QuestBuilder::getAllStories() {
	std::vector<StoryComponent*> stories;

	stories.emplace_back(intro());

	return stories;
}

StoryComponent* QuestBuilder::intro() {
	std::string description_story = "Introduction";
	std::string description_quest1 = "Talking";
	std::string description_task1 = "Talk to René";
	std::string name = "René";

	std::vector<TaskComponent*> tasks_quest1;

	tasks_quest1.emplace_back(&entity_manager.create_component<TaskComponent>(
		player, 
		description_task1 , 
		generate::NPCGenerator(multimedia_manager, entity_manager).generate_quest_npc(name, assets::spritesheets::HUMAN_MALE_1),
		1));

	std::vector<QuestComponent*> quests;

	quests.emplace_back(&entity_manager.create_component<QuestComponent>(player, description_quest1, tasks_quest1));


	return &entity_manager.create_component<StoryComponent>(player, description_story, quests);
}