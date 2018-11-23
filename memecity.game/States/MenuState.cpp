#include "MenuState.h"
#include "GameState.h"

void MenuState::on_load()
{

}

void MenuState::update(float dt)
{
	auto& input_manager = _context->input_manager;
	if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Up))
	{
		menu->next();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Down))
	{
		menu->previous();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Enter))
	{
		menu->select();
	}
	else if (input_manager.is_pressed(memecity::engine::sdl::InputKeys::Escape))
	{
		menu->back();
	}
}

void MenuState::draw()
{
	menu->render();
}

void MenuState::on_enter()
{
	_context->multimedia_manager.play_background_music("bgm-menu.mp3", 100);
}

void MenuState::on_exit()
{
	
}
