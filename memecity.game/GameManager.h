#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H

#include "MemeEngine.h"
#include <ECS.h>
#include "Generate\CityGenerator.h"

class GameManager : public memecity::engine::MemeEngine
{
private:
	memecity::engine::ecs::EntityManager entity_manager;
	generate::CityGenerator city_generator;

protected:
	void init() override;
	void update(float dt) override;
	void draw() override;
};


#endif
