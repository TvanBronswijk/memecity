#include "PauseMenuState.h"
#include <UI.h>

using namespace memecity::engine::ui::menu;

void PauseMenuState::on_load()
{
	auto resume_game = [&](MenuItem& menu_item) { back(); };
	auto main_menu = [&](MenuItem& menu_item) { back(2);  };

	menu = MenuBuilder(_context->multimedia_manager)
		.create_menu("Paused")
		.with_menu_item("Resume Game", nullptr, resume_game)
		.with_menu_item("Main menu", nullptr, main_menu)
		.get_menu();
}

void PauseMenuState::update(float dt)
{
	auto& input_manager = _context->input_manager;
	input_manager.update();
	if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Up) && debounce_counter == 0)
	{
		reset_debounce_counter();
		menu->next();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Down) && debounce_counter == 0)
	{
		reset_debounce_counter();
		menu->previous();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Enter) && debounce_counter == 0)
	{
		reset_debounce_counter();
		menu->select();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Escape) && debounce_counter == 0)
	{
		reset_debounce_counter();
		menu->back();
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

void PauseMenuState::draw()
{
	menu->render();
}

void PauseMenuState::on_enter()
{

}

void PauseMenuState::on_exit()
{

}
