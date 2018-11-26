#ifndef _PAUSE_MENU_STATE_H
#define _PAUSE_MENU_STATE_H
#include <Engine/State.h>
#include <UI.h>
#include "..\..\GameManager.h"

class PauseMenuState : public memecity::engine::state::State
{
private:
	GameManager::GameContext* _context;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
public:
	PauseMenuState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc);
	~PauseMenuState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};
#endif
