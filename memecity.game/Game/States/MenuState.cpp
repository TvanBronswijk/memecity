#include "MenuState.h"
#include "LoadingState.h"
#include "GameState.h"
#include "..\GameLoader.h"

MenuState::MenuState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc)
	: State(sm), _context(&gc)
{
	advanced_graphics_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Advanced Graphics")
		.with_back_menu_item()
		.get_menu();

	settings_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Settings")
		.with_menu_item("Enable fullscreen", nullptr, [&](auto& menu_item) { gc.get_multimedia_manager().set_fullscreen(true); })
		.with_menu_item("Disable fullscreen", nullptr, [&](auto& menu_item) { gc.get_multimedia_manager().set_fullscreen(false); })
		.with_menu_item("Advanced Graphics", advanced_graphics_menu.get())
		.with_back_menu_item()
		.get_menu();

	menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("MemeCity")
		.with_menu_item("Start Game", nullptr, [&](auto& menu_item) { next<LoadingState>(gc, [&](auto& ctx, auto& listener) { replace<GameState>(ctx, GameLoader(ctx, 16, 16).build(listener)); }); })
		.with_menu_item("Settings", settings_menu.get())
		.with_menu_item("Exit", nullptr, [&](auto& menu_item) { gc.get_input_manager().quit(); })
		.get_menu();
}

void MenuState::on_load()
{
}

void MenuState::update(float dt)
{
	auto& input_manager = _context->get_input_manager();
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
	_context->get_multimedia_manager().play_background_music("bgm-menu.mp3", 100);
}

void MenuState::on_exit()
{
	_context->get_multimedia_manager().pause_background_music();
}
