#include "GameState.h"
#include "../../Assets.h"
#include "../Systems/FightingSystem.h"

void GameState::on_load()
{
	_hud.create_overlay_text_item("HEALTH", "Health", 16, 100.0f, 20.0f);
	_hud.create_overlay_bar_item("HEALTHVALUE", 100, 20, 150, 12, 100, 200, memecity::engine::sdl::Color(255,0,0), memecity::engine::sdl::Color(0,255,0));
	_hud.create_overlay_text_item("SCORE", "Score:100", 16, 100, 40);
	_hud.create_overlay_text_item("EXP", "Exp:100", 16, 100, 60);

	_hud.create_overlay_text_item("S", "S: 1", 16, 400, 16);
	_hud.create_overlay_text_item("P", "P: 1", 16, 400, 32);
	_hud.create_overlay_text_item("E", "E: 1", 16, 400, 48);
	_hud.create_overlay_text_item("C", "C: 1", 16, 400, 64);
	_hud.create_overlay_text_item("I", "I: 1", 16, 500, 16);
	_hud.create_overlay_text_item("A", "A: 1", 16, 500, 32);
	_hud.create_overlay_text_item("L", "L: 1", 16, 500, 48);

	_hud.create_overlay_text_item("BLIKCOIN", "BlikCoin: 9999", 16, 650, 16);
}

void GameState::update(float dt)
{
	system_pool.update(entity_manager, memecity::engine::ecs::System::update);
}

void GameState::draw()
{
	system_pool.update(entity_manager, memecity::engine::ecs::System::draw);
	_hud.render();
}

void GameState::on_enter()
{
	_context->get_multimedia_manager().play_background_music(assets::music::DEFAULT_BGM);
}

void GameState::on_exit()
{
	_context->get_multimedia_manager().pause_background_music();
}
