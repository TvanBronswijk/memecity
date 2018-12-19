#ifndef _PAUSE_MENU_STATE_H
#define _PAUSE_MENU_STATE_H
#include <Engine/State.h>
#include <UI.h>
#include "..\..\GameManager.h"
#include "ECS/EntityManager.h"
#include "../PlayerManager.h"

class PauseMenuState : public memecity::engine::state::State
{
private:
	GameManager::GameContext* _context;
	memecity::engine::ecs::EntityManager* _entity_manager;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> help_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> help_menu2;
	int* _map_number;
	std::string* _save_slot;

public:
	PauseMenuState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, memecity::engine::ecs::EntityManager& em, int& map_number, std::string& save_slot);
	~PauseMenuState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};
#endif
