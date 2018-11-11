#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include "MemeEngine.h"
#include <ECS.h>
#include "Generate\CityGenerator.h"

class GameManager : public MemeEngine
{
private:
	ecs::EntityManager entity_manager;
	generate::CityGenerator city_generator;

protected:
	void init() override;
	void handle() override;

public:
	GameManager();
};


#endif
