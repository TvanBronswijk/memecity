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
#include "AISystem.h"
#include "MoveSystem.h"
#include "FightingSystem.h"
#include "AttackEvent.h"
#include "InteractionEvent.h"

class GameManager : public MemeEngine
{
private:
	ecs::EntityManager entity_manager;
	CityGenerator city_generator;
	InteractionEvent* interaction_event;
	AttackEvent* attack_event;

protected:
	void init() override;
	void handle() override;

public:
	GameManager();
};


#endif