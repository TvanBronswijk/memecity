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
#include "AnimationComponent.h"
#include "AnimationSystem.h"

class GameManager : public MemeEngine 
{
private:
	std::unique_ptr<CityGenerator> city_generator;
	std::unique_ptr<EntityManager> entity_manager;
	std::shared_ptr<AnimatedTexture> animated_texture;
	std::shared_ptr<TextTexture> text;
	EntityManager em;

protected:
	bool init() override;
	void handle() override;
};


#endif