#ifndef _QUESTBUILDER_H
#define  _QUESTBUILDER_H
#include <ECS.h>
#include <vector>
#include "..\Components.h"

class QuestBuilder{

private:

	memecity::engine::MultimediaManager& multimedia_manager;
	memecity::engine::ecs::EntityManager& entity_manager;
	memecity::engine::ecs::Entity& player;
	
	StoryComponent* intro();
public:
	std::vector<StoryComponent*> getAllStories();

	QuestBuilder(
		memecity::engine::MultimediaManager& multimedia_manager,memecity::engine::ecs::EntityManager& entity_manager,memecity::engine::ecs::Entity& player) :
		entity_manager(entity_manager), player(player), multimedia_manager(multimedia_manager) {}
};

#endif

