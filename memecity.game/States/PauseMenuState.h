#ifndef _PAUSE_MENU_STATE_H
#define _PAUSE_MENU_STATE_H
#include "Engine/State/State.h"
#include "../Menu/Menu.h"

class PauseMenuState : public memecity::engine::state::State
{
private:
	std::unique_ptr<menu::Menu> menu;

public:
	PauseMenuState(memecity::engine::state::StateMachine& sm)
		: State(sm) {}
	void init() override;
	void update(float dt) override;
	void draw() override;
	~PauseMenuState() = default;

};
#endif
