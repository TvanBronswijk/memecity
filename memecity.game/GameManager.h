#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include "MemeEngine.h"
#include "CityGenerator.h"
#include "DrawSystem.h"

class GameManager : public MemeEngine 
{
private:
	std::unique_ptr<CityGenerator> city_generator;
	std::unique_ptr<EntityManager> entity_manager;
	std::shared_ptr<AnimatedCharacter> animated_character;

protected:
	bool init() override;
	void handle() override;
};


#endif