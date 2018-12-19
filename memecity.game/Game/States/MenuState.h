#ifndef _MENU_STATE_H
#define _MENU_STATE_H

#include <Engine\State.h>
#include <UI.h>
#include "..\..\GameManager.h"
#include "ECS/EntityManager.h"

class MenuState : public memecity::engine::state::State
{
private:
	GameManager::GameContext* _context;
	std::unique_ptr<memecity::engine::ui::menu::Menu> start_new_game_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> load_save_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> settings_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> credits_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> highscores_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;

public:
	MenuState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc);
	~MenuState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif