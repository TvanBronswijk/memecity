#include "QuestBuilder.h"
#include "../Generate.h"
#include "../Enum/QuestStates.h"

using namespace memecity::engine::ecs;

std::vector<const memecity::engine::ecs::Entity*> QuestBuilder::getAllStories() {
	std::vector<const memecity::engine::ecs::Entity*> stories;

	stories.emplace_back(&intro());

	return stories;
}

const memecity::engine::ecs::Entity& QuestBuilder::intro() {
	std::string description_story = "Introduction";
	std::string description_quest1 = "Talking";
	std::string description_task1 = "Talk to Ren�";
	std::string description_task2 = "Talk to Ren�2";
	std::string name = "Ren�";

	std::vector<std::string> task_dialog_Ren� = {
		"Hello stranger!",
		"My name is Ren� and i work at Dumpert.",
		"Will you help me to create the best movie platform?",
		"Yess? thanks you!",
		"Here are some movies i would like you to make.",
		"and remember not in VVS",
		" "};

	std::vector<std::string> task_dialog_Ren�2 = {
	"You finished the intro!!"};

	auto builder = builder::EntityBuilder(this->entity_manager).create_entity();
	auto& story = builder.get();

	//create tasks
	std::deque<TaskComponent*> tasks_quest1{
		&entity_manager.create_component<TaskComponent>(
		const_cast<Entity&>(story),
		description_task1 ,
		Quest_State::Interaction,
		task_dialog_Ren�,
		&generate::NPCGenerator(multimedia_manager, entity_manager).generate_quest_npc(name, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1),
		&entity_manager.create_component<TaskComponent>(
		const_cast<Entity&>(story),
		description_task2 ,
		Quest_State::Interaction,
		task_dialog_Ren�2,
		&generate::NPCGenerator(multimedia_manager, entity_manager).generate_quest_npc(name, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1)
	};

	//create quests
	std::deque<QuestComponent*> quests{
	&entity_manager.create_component<QuestComponent>(const_cast<Entity&>(story), description_quest1, tasks_quest1)
	};

	//add quests
	builder.with_component<StoryComponent>(description_story, quests);

	return story;
}