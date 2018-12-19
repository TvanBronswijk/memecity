#include "MenuState.h"
#include "LoadingState.h"
#include "GameState.h"
#include "../../Assets.h"
#include "../Input.h"
#include "../Highscore.h"
#include "../HighscoreLoader.h"

MenuState::MenuState(memecity::engine::state::StateManager & sm, GameManager::GameContext & gc)
	: State(sm), _context(&gc)
{

	auto load_save_menu_builder = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager());
	load_save_menu_builder.create_menu("Load game", assets::fonts::DEFAULT_FONT);

	auto saves = gc.get_storage_manager().get_foldernames_from_directory(assets::saves::SAVE_LOCATION);

	for (std::string& save : saves)
	{
		load_save_menu_builder.with_menu_item(save, nullptr, [&,save](auto& menu_item) {next<GameState>(gc, true, save); });
	}

	load_save_menu = load_save_menu_builder.with_back_menu_item().get_menu();

	settings_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Settings", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Enable Fullscreen", nullptr, [&](auto& menu_item) { gc.get_multimedia_manager().set_fullscreen(true); })
		.with_menu_item("Disable Fullscreen", nullptr, [&](auto& menu_item) { gc.get_multimedia_manager().set_fullscreen(false); })
		.with_back_menu_item()
		.get_menu();

	credits_menu = memecity::engine::ui::menu::MenuBuilder(gc.get_multimedia_manager())
		.create_menu("Credits", assets::fonts::DEFAULT_FONT)
		.with_read_only_menu_item("Built by:")
		.with_read_only_menu_item(" ")
		.with_read_only_menu_item("Tobi van Bronswijk")
		.with_read_only_menu_item("Martijn van der Pol")
		.with_read_only_menu_item("Thom van de Pas")
		.with_read_only_menu_item("Rick van Berlo")
		.with_read_only_menu_item("Yoeri van Hoof")
		.with_read_only_menu_item("Simon Heij")
		.with_read_only_menu_item(" ")
		.with_read_only_menu_item("Honorable mention:")
		.with_read_only_menu_item("Roy van Oldenbeek")
		.with_read_only_menu_item(" ")
		.with_back_menu_item()
		.get_menu();
}

void MenuState::on_load()
{
}

void MenuState::update(float dt)
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

void MenuState::draw()
{
	menu->render();
}

void MenuState::on_enter()
{
	auto highscores_menu_builder = memecity::engine::ui::menu::MenuBuilder(get_context().get_multimedia_manager());
	highscores_menu_builder.create_menu("Highscores", assets::fonts::DEFAULT_FONT);

	HighscoreLoader loader;
	auto data = _context->get_storage_manager().load(assets::saves::SAVE_HIGHSCORES);
	loader.Load(data);

	for (auto score : loader.get_highscores())
	{
		highscores_menu_builder.with_read_only_menu_item(score.get_string());
	}

	highscores_menu = highscores_menu_builder
		.with_read_only_menu_item(" ")
		.with_back_menu_item()
		.get_menu();

	menu = memecity::engine::ui::menu::MenuBuilder(get_context().get_multimedia_manager())
		.create_menu("MemeCity", assets::fonts::DEFAULT_FONT)
		.with_menu_item("Start Game", nullptr, [&](auto& menu_item) { next<GameState>(get_context(), false); })
		.with_menu_item("Select Save", load_save_menu.get())
		.with_menu_item("Load Game", nullptr, [&](auto& menu_item) { next<GameState>(get_context(), true); })
		.with_menu_item("Settings", settings_menu.get())
		.with_menu_item("Highscores", highscores_menu.get())
		.with_menu_item("Credits", credits_menu.get())
		.with_menu_item("Exit", nullptr, [&](auto& menu_item) { get_context().get_input_manager().quit(); })
		.get_menu();

	_context->get_multimedia_manager().play_background_music(assets::music::MAIN_MENU_BGM);
}

void MenuState::on_exit()
{
	_context->get_multimedia_manager().pause_background_music();
}
