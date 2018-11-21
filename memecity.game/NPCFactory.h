#ifndef _NPCFACOTRY_H
#define  _NPCFACTORY_H
#include <ECS.h>
#include <vector>
#include <Engine\MultimediaManager.h>
#include "Components.h"

class NPCFactory{

private:
	memecity::engine::MultimediaManager& multimedia_manager;
	memecity::engine::sdl::TimerFacade& timer;
	memecity::engine::ecs::EntityManager entity_manager;
	
	float x, y;
	int level, strength, perception, endurance, charisma, intelligence, agility, luck, health;
	std::string animation_string;

public:

	NPCFactory(memecity::engine::MultimediaManager& multimedia_manager,
		memecity::engine::sdl::TimerFacade& timer,
		memecity::engine::ecs::EntityManager entity_manager) : multimedia_manager(multimedia_manager), timer(timer), entity_manager(entity_manager) {};

	//const memecity::engine::ecs::Entity& getNPC(int level);
	const memecity::engine::ecs::Entity& getRandomNPC(int level);
};

#endif

