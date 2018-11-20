#include "MenuState.h"
#include "../Menu/MenuBuilder.h"
#include "GameState.h"

void MenuState::init()
{
	auto& multimedia_manager = _state_machine.get_context().multimedia_manager;
	auto& input_manager = _state_machine.get_context().input_manager;

	auto enable_fullscreen = [&](menu::MenuItem& menu_item) { multimedia_manager.set_fullscreen(true); };
	auto disable_fullscreen = [&](menu::MenuItem& menu_item) { multimedia_manager.set_fullscreen(false); };

	advanced_graphics_menu = menu::MenuBuilder(multimedia_manager, input_manager)
		.create_menu("Advanced Graphics")
		.with_back_menu_item()
		.get_menu();

	settings_menu = menu::MenuBuilder(multimedia_manager, input_manager)
		.create_menu("Settings")
		.with_menu_item<menu::MenuItem>("Enable fullscreen", nullptr, enable_fullscreen)
		.with_menu_item<menu::MenuItem>("Disable fullscreen", nullptr, disable_fullscreen)
		.with_menu_item<menu::MenuItem>("Advanced Graphics", advanced_graphics_menu.get())
		.with_back_menu_item()
		.get_menu();

	auto start_game = [&](menu::MenuItem& menu_item) { _state_machine.create_state<GameState>(); };
	auto exit = [&](menu::MenuItem& menu_item) {input_manager.quit(); };

	menu = menu::MenuBuilder(multimedia_manager, input_manager)
		.create_menu("MemeCity")
		.with_menu_item<menu::MenuItem>("Start Game", nullptr, start_game)
		.with_menu_item<menu::MenuItem>("Settings", settings_menu.get())
		.with_menu_item<menu::MenuItem>("Exit", nullptr, exit)
		.get_menu();
}

void MenuState::update(float dt)
{
}

void MenuState::draw()
{
	menu->render();
	menu->handle_input();
}
