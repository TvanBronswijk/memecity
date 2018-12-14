#include "QuestBuilder.h"
#include "..\Generate.h"
#include "..\Enum\QuestStates.h"
#include "..\Quest\Quest.h"
#include "..\Quest\Task.h"
#include "..\Components\AIComponent.h"

using namespace memecity::engine::ecs;

std::vector<Story> QuestBuilder::getAllStories() {
	std::vector<Story> stories;

	stories.emplace_back(intro());

	return stories;
}

Story QuestBuilder::intro() {
	std::string name = "René";
	std::vector<std::string> task_dialog_René = {
		"Hello stranger!",
		"My name is René and i work at Dumpert.",
		"Will you help me to create the best movie platform?",
		"Yess? thanks you!",
		"Here are some movies i would like you to make.",
		"and remember not in VVS",
		" "};

	std::vector<std::string> task_dialog_René2 = {
	"pick up a tin can",
	" "};

	//create tasks
	std::deque<Task> tasks_quest1{
		Task{
		"Talk to René" ,
		Quest_State::Interaction,
		task_dialog_René,
		&npc_generator.generate_quest_npc(name, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1},
		Task{
		"Talk to René2" ,
		Quest_State::Interaction,
		task_dialog_René2,
		&npc_generator.generate_quest_npc(name, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest2{
		Task{
		"pick up a tin can" ,
		Quest_State::Finding,
		std::vector<std::string>(),
		&(entity_manager.get_entities_by_type("Blik").front().get()),
		nullptr,
		1}
	};


	std::deque<Task> tasks_quest3{
		Task{
		"Kill a human" ,
		Quest_State::Fighting,
		std::vector<std::string>(),
		&entity_manager.get_entities_with_component<AIComponent>()[0].get(),
		nullptr,
		1}
	};

	//create quests
	std::deque<Quest> quests{
	Quest{"Talking", tasks_quest1},
	Quest{"Picking Up", tasks_quest2},
	Quest{"Killing", tasks_quest3}
	};

	//add quests
	Story story{ "introduction", quests };

	return story;
}