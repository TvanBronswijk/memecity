#ifndef _MENU_STATE_H
#define _MENU_STATE_H
#include <Engine/State.h>
#include <UI.h>

class MenuState : public memecity::engine::state::State
{
private:

	std::unique_ptr<memecity::engine::ui::menu::Menu> advanced_graphics_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> settings_menu;
	std::unique_ptr<memecity::engine::ui::menu::Menu> menu;

public:
	MenuState(memecity::engine::state::StateManager& sm, memecity::engine::state::StateContext& sc)
		: State(sm, sc) 
	{
		advanced_graphics_menu = memecity::engine::ui::menu::MenuBuilder(sc.multimedia_manager)
			.create_menu("Advanced Graphics")
			.with_back_menu_item()
			.get_menu();

		settings_menu = memecity::engine::ui::menu::MenuBuilder(sc.multimedia_manager)
			.create_menu("Settings")
			.with_menu_item("Enable fullscreen", nullptr, [&](auto& menu_item) { sc.multimedia_manager.set_fullscreen(true); })
			.with_menu_item("Disable fullscreen", nullptr, [&](auto& menu_item) { sc.multimedia_manager.set_fullscreen(false); })
			.with_menu_item("Advanced Graphics", advanced_graphics_menu.get())
			.with_back_menu_item()
			.get_menu();

		menu = memecity::engine::ui::menu::MenuBuilder(sc.multimedia_manager)
			.create_menu("MemeCity")
			.with_menu_item("Start Game", nullptr, [&](auto& menu_item) { next<GameState>(*_context); })
			.with_menu_item("Settings", settings_menu.get())
			.with_menu_item("Exit", nullptr, [&](auto& menu_item) { sc.input_manager.quit(); })
			.get_menu();
	}
	
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	~MenuState() = default;

};

#endif

