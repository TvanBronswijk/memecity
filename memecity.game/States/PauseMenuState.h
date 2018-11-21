#ifndef _PAUSE_MENU_STATE_H
#define _PAUSE_MENU_STATE_H
#include "Engine/State/State.h"
#include <UI.h>

class PauseMenuState : public memecity::engine::state::State
{
private:
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
	int debounce_counter;
	int reset_debounce_counter()
	{
		return debounce_counter = 10;
	}

public:
	PauseMenuState(memecity::engine::state::StateMachine& sm)
		: State(sm) {}
	void init() override;
	void update(float dt) override;
	void draw() override;
	~PauseMenuState() = default;

};
#endif
