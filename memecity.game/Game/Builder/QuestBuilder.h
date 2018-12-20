#ifndef _QUESTBUILDER_H
#define  _QUESTBUILDER_H
#include <ECS.h>
#include <vector>
#include "..\Quest\Story.h"
#include "..\Generate\NPC\NPCGenerator.h"
#include "..\Generate\Item\ItemGenerator.h"

class QuestBuilder{

private:
	int tile_size = 48;
	int width = 128;
	int height = 128;
	Point start_player;

	memecity::engine::MultimediaManager* multimedia_manager;
	memecity::engine::ecs::EntityManager* entity_manager;
	std::unique_ptr<generate::NPCGenerator> npc_generator;
	
	Story intro();
	Story Rene();
	Story Johnny();
	Story Appie();
	Story chewing_gum_challenge();
public:
	std::vector<Story> get_all_stories();

	QuestBuilder(
		memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::ecs::EntityManager& entity_manager, Point player_start) :
		entity_manager(&entity_manager), multimedia_manager(&multimedia_manager), npc_generator(std::make_unique<generate::NPCGenerator>(multimedia_manager,entity_manager)), start_player(player_start) {}
};

#endif

