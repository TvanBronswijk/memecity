#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include "MemeEngine.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "CityGenerator.h"
#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "PlayerComponent.h"
#include "../memecity.engine.ecs/Entity.h"
#include "ExpComponent.h"
#include "ExpSystem.h"
#include "StatsComponent.h"

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
