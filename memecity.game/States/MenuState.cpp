#include "MenuState.h"
#include "GameState.h"
#include <UI.h>

using namespace memecity::engine::ui::menu;

void MenuState::init()
{
	auto& multimedia_manager = _state_machine.get_context().multimedia_manager;
	auto& input_manager = _state_machine.get_context().input_manager;

	auto enable_fullscreen = [&](MenuItem& menu_item) { multimedia_manager.set_fullscreen(true); };
	auto disable_fullscreen = [&](MenuItem& menu_item) { multimedia_manager.set_fullscreen(false); };

	advanced_graphics_menu = MenuBuilder(multimedia_manager, input_manager)
		.create_menu("Advanced Graphics")
		.with_back_menu_item()
		.get_menu();

	settings_menu = MenuBuilder(multimedia_manager, input_manager)
		.create_menu("Settings")
		.with_menu_item("Enable fullscreen", nullptr, enable_fullscreen)
		.with_menu_item("Disable fullscreen", nullptr, disable_fullscreen)
		.with_menu_item("Advanced Graphics", advanced_graphics_menu.get())
		.with_back_menu_item()
		.get_menu();

	auto start_game = [&](MenuItem& menu_item) { _state_machine.create_state<GameState>(); };
	auto exit = [&](MenuItem& menu_item) {input_manager.quit(); };

	menu = MenuBuilder(multimedia_manager, input_manager)
		.create_menu("MemeCity")
		.with_menu_item("Start Game", nullptr, start_game)
		.with_menu_item("Settings", settings_menu.get())
		.with_menu_item("Exit", nullptr, exit)
		.get_menu();
}

void MenuState::update(float dt)
{
}

void MenuState::draw()
{
	menu->render();

	auto& input_manager = _state_machine.get_context().input_manager;
	input_manager.update();
	if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Up) && debounce_counter == 0)
	{
		menu->handle_up();
		reset_debounce_counter();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Down) && debounce_counter == 0)
	{
		menu->handle_down();
		reset_debounce_counter();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Enter) && debounce_counter == 0)
	{
		menu->handle_enter();
		reset_debounce_counter();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Escape) && debounce_counter == 0)
	{
		menu->handle_escape();
		reset_debounce_counter();
	}
	else
	{
		debounce_counter--;
		if (debounce_counter < 0)
		{
			debounce_counter = 0;
		}
	}
}
