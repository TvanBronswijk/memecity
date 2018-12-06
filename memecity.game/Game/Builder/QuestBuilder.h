#ifndef _QUESTBUILDER_H
#define  _QUESTBUILDER_H
#include <ECS.h>
#include <vector>
#include "..\Components.h"
#include "..\Generate\NPC\NPCGenerator.h"

class QuestBuilder{

private:

	memecity::engine::MultimediaManager& multimedia_manager;
	memecity::engine::ecs::EntityManager& entity_manager;
	generate::NPCGenerator npc_generator;
	
	const memecity::engine::ecs::Entity& intro();
public:
	std::vector<const memecity::engine::ecs::Entity*> getAllStories();

	QuestBuilder(
		memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::ecs::EntityManager& entity_manager) :
		entity_manager(entity_manager), multimedia_manager(multimedia_manager), npc_generator(generate::NPCGenerator(multimedia_manager,entity_manager)) {}
};

#endif

