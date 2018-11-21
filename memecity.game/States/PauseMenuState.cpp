#include "PauseMenuState.h"
#include <UI.h>

using namespace memecity::engine::ui::menu;

void PauseMenuState::init()
{
	auto resume_game = [&](MenuItem& menu_item) { _state_machine.pop(); };
	auto main_menu = [&](MenuItem& menu_item) { _state_machine.pop(); _state_machine.pop(); };


	menu = memecity::engine::ui::menu::MenuBuilder(_state_machine.get_context().multimedia_manager, _state_machine.get_context().input_manager)
		.create_menu("Paused")
		.with_menu_item("Resume Game", nullptr, resume_game)
		.with_menu_item("Main menu", nullptr, main_menu)
		.get_menu();
}

void PauseMenuState::update(float dt)
{
}

void PauseMenuState::draw()
{
	menu->render();
	menu->handle_input();
}
