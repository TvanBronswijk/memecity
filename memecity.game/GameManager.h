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
#include "InteractionSystem.h"
#include "Event.h"

class GameManager : public MemeEngine 
{
private:
	std::unique_ptr<CityGenerator> city_generator;
	std::unique_ptr<EntityManager> entity_manager;
	std::shared_ptr<AnimatedCharacter> animated_character;
	std::shared_ptr<Texture> text;
	InteractionEvent* interaction_event;

protected:
	bool init() override;
	void handle() override;
};


#endif