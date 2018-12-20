#include "QuestBuilder.h"
#include "..\Generate.h"
#include "..\Enum\QuestStates.h"
#include <stdlib.h>
#include "..\Quest\Quest.h"
#include "..\Quest\Task.h"
#include "..\Components\AIComponent.h"
#include "..\Components.h"

using namespace memecity::engine::ecs;

std::vector<Story> QuestBuilder::get_all_stories() {
	std::vector<Story> stories;

	stories.emplace_back(intro());
	stories.emplace_back(Rene());
	stories.emplace_back(Johnny());
	stories.emplace_back(Appie());
	stories.emplace_back(chewing_gum_challenge());

	return stories;
}

Story QuestBuilder::Rene() {
	std::string rene = "Rene";

	std::deque<Task> tasks_quest1{
		Task{
		"Talking to " + rene,
		Quest_State::Interaction,
		{"Heyy my name is Rene",
		"Nobody is posting new content on dumpert...",
		"Can you help me?",
		"Fighting clips are always a hit.",
		"I will pay you well.",
		"please help me!!"
		" "},
		&npc_generator->generate_quest_npc(rene, (rand() % (width * tile_size)) ,(rand() % (height * tile_size)), assets::spritesheets::BOY_1),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest2{
		Task{
		"Fight handhaving",
		Quest_State::Fighting,
		{},
		&npc_generator->generate_police_npc((rand() % (width * tile_size)) ,(rand() % (height * tile_size))),
		nullptr,
		5}
	};
	std::deque<Task> tasks_quest3{
		Task{
		"Talking to " + rene,
		Quest_State::Interaction,
		{"Thanks!",
		"This clip will go viral!"
		" "},
		&npc_generator->generate_quest_npc(rene, 0,0, assets::spritesheets::BOY_1),
		nullptr,
		1}
	};


	//create quests
	std::deque<Quest> quests{
	Quest{"Talking", tasks_quest1},
	Quest{"Droping", tasks_quest2},
	Quest{"Talking", tasks_quest3}
	};

	//add quests
	Story story{ "Help dumpert",200,2000, quests };

	return story;

}
Story QuestBuilder::Johnny() {
	std::string johnny = "Johnny";
	
	for (size_t i = 0; i < 20; i++) {
		generate::ItemGenerator(*multimedia_manager, *entity_manager).make_item("Tin can", "a normal tin can", 0, 0, 0, 0, 0, 0, 0, (rand() % (width * tile_size)), (rand() % (height * tile_size)), 48, 48, assets::sprites::TOMATO);
	}

	std::deque<Task> tasks_quest1{
		Task{
		"Talking to " + johnny,
		Quest_State::Interaction,
		{"heyy do you know this song?",
		"TOTO TOTOMATE PLUKKER",
		"NO? can you get 5 tomato's for me?",
		"Then you will understand what the song means."
		" "},
		&npc_generator->generate_quest_npc(johnny, (rand() % (width * tile_size)) ,(rand() % (height * tile_size)), assets::spritesheets::BOY_1),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest2{
		Task{
		"Find tomato's",
		Quest_State::Finding,
		{},
		generate::ItemGenerator(*multimedia_manager, *entity_manager).make_item("Tomato", "round juicy opbject", 0, 0, 0, 0, 0, 0, 0,(rand() % (width * tile_size)) ,(rand() % (height * tile_size)), 48, 48, assets::sprites::TOMATO),
		nullptr,
		5}
	};
	std::deque<Task> tasks_quest3{
		Task{
		"Talking to " + johnny,
		Quest_State::Interaction,
		{"TOTO TOTOMATE PLUKKER",
		"Sing it with me!"
		"TOTO TOTOMATE PLUKKER",
		" "},
		&npc_generator->generate_quest_npc(johnny, 0,0, assets::spritesheets::BOY_1),
		nullptr,
		1}
	};


	//create quests
	std::deque<Quest> quests{
	Quest{"Talking", tasks_quest1},
	Quest{"Droping", tasks_quest2},
	Quest{"Talking", tasks_quest3}
	};

	//add quests
	Story story{ "TOTO TOTOMATE PLUKKER",150,200, quests };

	return story;

}
Story QuestBuilder::Appie() {
	std::string appie = "Appie";

	const memecity::engine::ecs::Entity* water_tile = nullptr;

	auto tiles = entity_manager->get_entities_by_type("tile");
	for (std::vector<std::reference_wrapper<const memecity::engine::ecs::Entity>>::iterator it = tiles.begin(); it != tiles.end(); ++it) {
		auto tile_component = (it)->get().get<TileComponent>();
		if (tile_component->type == "Water") {
			water_tile = &tile_component->entity();
			break;
		}
	}

	std::deque<Task> tasks_quest1{
		Task{
		"Talking to " + appie,
		Quest_State::Interaction,
		{"heyy.",
		"I drunk HAHAHA",
		"Tin can water",
		"HAHAHA"
		" "},
		&npc_generator->generate_quest_npc(appie, (rand() % (width * tile_size)) ,(rand() % (height * tile_size)), assets::spritesheets::BOY_2),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest2{
		Task{
		"Throw tin can in the water",
		Quest_State::Dropping,
		{},
		water_tile,
		generate::ItemGenerator(*multimedia_manager, *entity_manager).make_item("Tin can", "a normal tin can", 0, 0, 0, 0, 0, 0, 0, (rand() % (width * tile_size)) ,(rand() % (height * tile_size)), 48, 48, assets::sprites::TIN_CAN),
		1}
	};
	std::deque<Task> tasks_quest3{
		Task{
		"Talking to " + appie,
		Quest_State::Interaction,
		{"Who are you ?",
		"Did i talk  to you ?",
		"What did i say?",
		"Really! HAHAHA okay you did well.",
		" "},
		&npc_generator->generate_quest_npc(appie, 0,0, assets::spritesheets::BOY_3),
		nullptr,
		1}
	};


	//create quests
	std::deque<Quest> quests{
	Quest{"Talking", tasks_quest1},
	Quest{"Droping", tasks_quest2},
	Quest{"Talking", tasks_quest3}
	};

	//add quests
	Story story{ "Tin can in water",1200,1000, quests };

	return story;
	
}
Story QuestBuilder::chewing_gum_challenge() {
	std::string child = "child";


	std::deque<Task> tasks_quest1{
		Task{
		"Talking to " + child,
		Quest_State::Interaction,
		{"Hey could you help me?",
		"I would like to do the chewing gum challenge",
		"But i dont have any money ?",
		"Can you get me some?",
		"Yess? thanks I will wait here."
		" "},
		&npc_generator->generate_quest_npc(child, (rand() % (width * tile_size)) ,(rand() % (height * tile_size)), assets::spritesheets::BOY_3),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest2{
		Task{
		"Find chewing gum",
		Quest_State::Finding,
		{},
		generate::ItemGenerator(*multimedia_manager, *entity_manager).make_item("chewing gum", "chew chew .......", 0, 0, 0, 0, 0, 0, 0, (rand() % (width * tile_size)) ,(rand() % (height * tile_size)), 48, 48, assets::sprites::CHEWING_GUM),
		nullptr,
		1}
	};
	std::deque<Task> tasks_quest3{
		Task{
		"Talking to " + child,
		Quest_State::Interaction,
		{"Thank you very much sir!",
		"Here take my blikcoins.",
		"I know it is not a lot but it is something."
		" "},
		&npc_generator->generate_quest_npc(child, 0,0, assets::spritesheets::BOY_3),
		nullptr,
		1}
	};


	//create quests
	std::deque<Quest> quests{
	Quest{"Talking", tasks_quest1},
	Quest{"Finding", tasks_quest2},
	Quest{"Talking", tasks_quest3}
	};

	//add quests
	Story story{ "chewing gum challenge",100,10, quests };

	return story;
}

Story QuestBuilder::intro() {
	std::string violet = "Violet";
	std::string simon = "Simon";
	std::string yoeri = "Yoeri";

	int x = (rand() % (tile_size * 2) + start_player.x);
	int y = (rand() % (tile_size * 2) + start_player.y);
	//create tasks
	std::deque<Task> tasks_quest1{
		Task{
		"Talk to " + violet ,
		Quest_State::Interaction,
		{ "Welcome Stranger!",
		"This is memecity.",
		"A city full of adventure",
		"when you press 'n'",
		"You can see your task you need to complete.",
		"First I will show you how to do a basic task.",
		"please interact with Simon over there.",
		" "},
		&npc_generator->generate_quest_npc(violet, start_player.x,start_player.y - (tile_size * 1), assets::spritesheets::GIRL_1),
		nullptr,
		1},
		Task{
		"Talk to " + simon ,
		Quest_State::Interaction,
		{"Hello",
		"my name is Simon.",
		"Do you know all the inputs in this game? No?",
		"You can find them when you press escape->help.",
		"Have a nice day!",
		" "},
		&npc_generator->generate_quest_npc(simon,x + (tile_size * 3),y, assets::spritesheets::BOY_1),
		nullptr,
		1},
		Task{
		"Talk to " + violet ,
		Quest_State::Interaction,
		{"Have you talked to Simon?",
		"yess? great. Now you know how to use all the inputs.",
		"Lets try to pick up some stuff.",
		"Please pick up that can for me.",
		" ",},
		&npc_generator->generate_quest_npc(violet,0,0, assets::spritesheets::GIRL_1),
		nullptr,
		1},
	};

	std::deque<Task> tasks_quest2{
		Task{
		"pick up a tin can" ,
		Quest_State::Finding,
		{},
		generate::ItemGenerator(*multimedia_manager, *entity_manager).make_item("Tin can", "a normal tin can", 0, 0, 0, 0, 0, 0, 0,(rand() % (width * tile_size)) ,(rand() % (height * tile_size)), 48, 48, assets::sprites::TIN_CAN),
		nullptr,
		1}
	};
	
	std::deque<Task> tasks_quest3{
		Task{
		"Talk to " + violet,
		Quest_State::Interaction,
		{"Good job you have pick up every item you want.",
		"the last task i would like you to do is to fight yoeri",
		"Be aware he is very angry!"
		" "},
		&npc_generator->generate_quest_npc(violet, 0,0, assets::spritesheets::GIRL_1),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest4{
		Task{
		"Fight " + yoeri,
		Quest_State::Fighting,
		{"go away!!"},
		&npc_generator->generate_npc(x,y - (tile_size * 3),48,48,10,60,100,10,1,1,1,1,1,1,1,yoeri,Ai_State::Idle,{" "},1,assets::spritesheets::BOY_2),
		nullptr,
		1}
	};

	std::deque<Task> tasks_quest5{
		Task{
		"Talking to " + violet,
		Quest_State::Interaction,
		{"Is he dead? i didn't say you need to kill him!!!",
		"Ow well, one less to worry about i think.",
		"know you know how to fight but be aware. people will fight back.",
		"These are all the basic task you need to know for these cities.",
		"Go explore and adventure these big cities!",
		" "},
		&npc_generator->generate_quest_npc(violet, 0,0, assets::spritesheets::GIRL_1),
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
	Story story{ "introduction",210,200, quests };

	return story;
}