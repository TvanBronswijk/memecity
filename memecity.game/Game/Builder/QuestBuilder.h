#ifndef _QUESTBUILDER_H
#define  _QUESTBUILDER_H
#include <ECS.h>
#include <vector>
#include "..\Quest\Story.h"
#include "..\Generate\NPC\NPCGenerator.h"
#include "..\Generate\Item\ItemGenerator.h"

class QuestBuilder{

private:

	memecity::engine::MultimediaManager* multimedia_manager;
	memecity::engine::ecs::EntityManager* entity_manager;
	std::unique_ptr<generate::NPCGenerator> npc_generator;
	
	Story intro();
public:
	std::vector<Story> get_all_stories();

	QuestBuilder(
		memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::ecs::EntityManager& entity_manager) :
		entity_manager(&entity_manager), multimedia_manager(&multimedia_manager), npc_generator(std::make_unique<generate::NPCGenerator>(multimedia_manager,entity_manager)) {}
};

#endif

