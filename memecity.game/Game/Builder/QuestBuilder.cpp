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
	std::string roy = "Roy van Oldenbeek";
	std::string simon = "Simon Heij";
	std::string yoeri = "Yoeri van Hoof";


	//create tasks
	std::deque<Task> tasks_quest1{
		Task{
		"Talk to " + roy ,
		Quest_State::Interaction,
		{ "Welcome Stranger!",
		"This is memecity.",
		"A city full of adventure",
		"when you press 'n' youo can see your task you need to compleet."
		"First I will show you how to do basic task.",
		"please interact with Simon over there.",
		" "},
		&npc_generator.generate_quest_npc(roy, 0,0, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1},
		Task{
		"Talk to " + simon ,
		Quest_State::Interaction,
		{"Hello",
		"my name is Simon.",
		"Do you know all the inputs in this game? no?",
		"You can find them when you press escape->help.",
		"Have a nice day!",
		" "},
		&npc_generator.generate_quest_npc(simon,300,0, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1},
		Task{
		"Talk to " + roy ,
		Quest_State::Interaction,
		{"Have you talked to Simon?",
		"yess? great. Now you know how to use all the inputs.",
		"Lets try to pick up some stuff.",
		"Please pick up that can for me.",
		" ",},
		&npc_generator.generate_quest_npc(roy,0,0, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1},
	};

	auto item = item_generator.MakeItem("Tin can", "a normal tin can", 0, 0, 0, 0, 0, 0, 0, 50, 0, 48, 48, assets::sprites::TIN_CAN);

	std::deque<Task> tasks_quest2{
		Task{
		"pick up a tin can" ,
		Quest_State::Finding,
		{},
		item,
		nullptr,
		1}
	};
	
	std::deque<Task> tasks_quest3{
		Task{
		"Talk to " + roy,
		Quest_State::Interaction,
		{"Good job you pick up every item you want.",
		"the last task i would like you to do is to fight yoeri",
		"Be aware he is very angry!"
		" "},
		&npc_generator.generate_quest_npc(roy, 0,0, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest4{
		Task{
		"Fight" + yoeri,
		Quest_State::Fighting,
		{"go away!!"},
		&npc_generator.generate_npc(0,50,48,48,10,60,180,1,1,1,1,1,1,1,yoeri,State::Idle,{" "},assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest5{
		Task{
		"Talking to " + roy,
		Quest_State::Interaction,
		{"Is he dead? i didn't say you need to kill him!!!",
		"Ow well, one less to worry about i think.",
		"know you know how to fight but be aware. people will fight back."
		" "},
		&npc_generator.generate_quest_npc(roy, 0,0, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1}
	};


	//create quests
	std::deque<Quest> quests{
	Quest{"Talking", tasks_quest1},
	Quest{"Picking Up", tasks_quest2},
	Quest{"Talking", tasks_quest3},
	Quest{"Fighting", tasks_quest4},
	Quest{"Talking", tasks_quest5},
	};

	//add quests
	Story story{ "introduction", quests };

	return story;
}