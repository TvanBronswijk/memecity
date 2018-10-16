#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include "MemeEngine.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include "PositionComponent.h"
#include "AIComponent.h"
#include "VelocityComponent.h"
#include "LevelComponent.h"
#include "HealthComponent.h"
#include "AISystem.h"




class GameManager : public MemeEngine{
private:
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Texture> text;

protected:
	bool init() override;
	void handle() override;

};


#endif