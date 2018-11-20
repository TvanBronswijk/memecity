#include "PauseMenuState.h"
#include "../Menu/MenuBuilder.h"

void PauseMenuState::init()
{
	auto resume_game = [&](menu::MenuItem& menu_item) { _state_machine.pop(); };
	auto main_menu = [&](menu::MenuItem& menu_item) { _state_machine.pop(); _state_machine.pop(); };


	menu = menu::MenuBuilder(_state_machine.get_context().multimedia_manager, _state_machine.get_context().input_manager)
		.create_menu("Paused")
		.with_menu_item<menu::MenuItem>("Resume Game", nullptr, resume_game)
		.with_menu_item<menu::MenuItem>("Main menu", nullptr, main_menu)
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
