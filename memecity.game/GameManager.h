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
	std::unique_ptr<menu::Menu> advanced_graphics_menu;
	std::unique_ptr<menu::Menu> settings_menu;
	std::unique_ptr<menu::Menu> menu;
	
protected:
	void init() override;
	void update(float dt) override;
	void draw() override;
};


#endif
