#include "StoryState.h"
#include "..\..\Assets.h"
#include "..\Input.h"

StoryState::StoryState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc)
	: State(sm), _context(&gc)
{

	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Stories", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Back", nullptr, [&](auto& menu_item) { back(); })
		.with_menu_item("Help", help_menu.get())
		.with_menu_item("Main Menu", nullptr, [&](auto& menu_item) { back(2);  })
		.get_menu();
}

void StoryState::on_load()
{

}

void StoryState::update(float dt)
{
	auto& input_manager = _context->get_input_manager();
	if (input_manager.is_pressed(input::UP))
	{
		menu->next();
	}
	else if (input_manager.is_pressed(input::DOWN))
	{
		menu->previous();
	}
	else if (input_manager.is_pressed(input::ENTER))
	{
		menu->select();
	}
	else if (input_manager.is_pressed(input::ESCAPE))
	{
		menu->back();
	}
}

void StoryState::draw()
{
	menu->render();
}

void StoryState::on_enter()
{

}

void StoryState::on_exit()
{

}
