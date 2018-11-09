#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include "MemeEngine.h"
#include <ECS.h>
#include "CityGenerator.h"
#include "DrawSystem.h"
#include "InputSystem.h"
#include "MoveSystem.h"
#include "PlayerComponent.h"
#include "StatsComponent.h"
#include "AnimationSystem.h"

class GameManager : public MemeEngine
{
private:
	ecs::EntityManager entity_manager;
	CityGenerator city_generator;

protected:
	void init() override;
	void handle() override;

public:
	GameManager();
};


#endif