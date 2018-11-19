#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include <Engine.h>
#include <ECS.h>
#include "Generate.h"
#include "Menu/Menu.h"

class GameManager : public memecity::engine::MemeEngine
{
private:
	memecity::engine::ecs::EntityManager entity_manager;
	generate::CityGenerator city_generator;
	menu::Menu menu {multimedia_manager, input_manager};
protected:
	void init() override;
	void update(float dt) override;
	void draw() override;
};


#endif
