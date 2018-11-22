#ifndef _MENU_STATE_H
#define _MENU_STATE_H

#include "Engine/State/State.h"
#include <UI.h>

class MenuState : public memecity::engine::state::State
{
private:

	std::unique_ptr<memecity::engine::ui::menu::Menu> advanced_graphics_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> settings_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
	int debounce_counter;
	int reset_debounce_counter()
	{
		return debounce_counter = 10;
	}
	bool left_state;

public:
	MenuState(memecity::engine::state::StateMachine& sm, memecity::engine::state::StateContext& sc)
		: State(sm, sc), debounce_counter(reset_debounce_counter()), left_state(true) {}
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	~MenuState() = default;

};

#endif

