#ifndef _PAUSE_MENU_STATE_H
#define _PAUSE_MENU_STATE_H
#include <Engine/State.h>
#include <UI.h>

class PauseMenuState : public memecity::engine::state::State
{
private:
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;
public:
	PauseMenuState(memecity::engine::state::StateManager& sm, memecity::engine::state::StateContext& sc)
		: State(sm, sc) 
	{
		menu = memecity::engine::ui::menu::MenuBuilder(_context->multimedia_manager)
			.create_menu("Paused")
			.with_menu_item("Resume Game", nullptr, [&](auto& menu_item) { back(); })
			.with_menu_item("Main menu", nullptr, [&](auto& menu_item) { back(2);  })
			.get_menu();
	}

	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	~PauseMenuState() = default;

};
#endif
