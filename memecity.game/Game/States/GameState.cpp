#include "GameState.h"
#include "../../Assets.h"
#include "../Systems/HudSystem.h"
#include "../Systems/FightingSystem.h"

GameState::GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc,
	memecity::engine::ecs::EntityManager em) : _context(&gc), entity_manager(std::move(em)), State(sm), _hud(_context->get_multimedia_manager(), _context->get_multimedia_manager().get_texture("Sprites/big_black.bmp", 0, 0, _context->get_multimedia_manager().get_screen_width(), 100), 0, 0)
{
	auto& hud_system = entity_manager.create_system<HudSystem>(memecity::engine::ecs::System::draw, _hud);

	FightingSystem* system = dynamic_cast<FightingSystem*>(entity_manager.get_system_of_type<FightingSystem>());

	memecity::engine::ecs::eventing::bind(system->health_event, &hud_system, &HudSystem::on_health_changed);

}

void GameState::on_load()
{
	
	_hud.create_overlay_text_item("HEALTH", "Health", 16, 100.0f, 20.0f);
	_hud.create_overlay_bar_item("HEALTHVALUE", 100, 20, 150, 12);
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
	entity_manager.update(memecity::engine::ecs::System::update);
	
}

void GameState::draw()
{
	entity_manager.update(memecity::engine::ecs::System::draw);
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
