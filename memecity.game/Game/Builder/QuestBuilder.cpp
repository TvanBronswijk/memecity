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

	auto builder = entity_manager.create_entity("story");
	auto& story = builder.get();

	//create tasks
	std::deque<TaskComponent*> tasks_quest1{
		&entity_manager.create_component<TaskComponent>(
		const_cast<Entity&>(story),
		"Talk to René" ,
		Quest_State::Interaction,
		task_dialog_René,
		&npc_generator.generate_quest_npc(name, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1),
		&entity_manager.create_component<TaskComponent>(
		const_cast<Entity&>(story),
		"Talk to René2" ,
		Quest_State::Interaction,
		task_dialog_René2,
		&npc_generator.generate_quest_npc(name, assets::spritesheets::HUMAN_MALE_1),
		nullptr,
		1)
	};

	std::deque<TaskComponent*> tasks_quest2{
		&entity_manager.create_component<TaskComponent>(
		const_cast<Entity&>(story),
		"pick up a tin can" ,
		Quest_State::Finding,
		std::vector<std::string>(),
		&(entity_manager.get_entities_by_type("Blik").front().get()),
		nullptr,
		1),
	};


	std::deque<TaskComponent*> tasks_quest3{
		&entity_manager.create_component<TaskComponent>(
		const_cast<Entity&>(story),
		"Kill a human" ,
		Quest_State::Fighting,
		std::vector<std::string>(),
		&entity_manager.get_entities_with_component<AIComponent>()[0].get(),
		nullptr,
		1),
	};

	//create quests
	std::deque<QuestComponent*> quests{
	&entity_manager.create_component<QuestComponent>(const_cast<Entity&>(story), "Talking", tasks_quest1),
	&entity_manager.create_component<QuestComponent>(const_cast<Entity&>(story), "Picking Up", tasks_quest2),
	&entity_manager.create_component<QuestComponent>(const_cast<Entity&>(story), "Killing", tasks_quest3)
	};

	//add quests
	builder.with_component<StoryComponent>("introduction", quests);

	return story;
}