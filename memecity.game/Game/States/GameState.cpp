#include "GameState.h"
#include "../Systems/HudSystem.h"
#include "../Systems/FightingSystem.h"


GameState::GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc,
	memecity::engine::ecs::EntityManager em) : State(sm), _context(&gc), entity_manager(std::move(em)), _hud(_context->get_multimedia_manager(), _context->get_multimedia_manager().get_texture("big_black.bmp", 0, 0, _context->get_multimedia_manager().get_screen_width(), 100), 0, 0)
{
	
}

void GameState::on_load()
{

	auto& hud_system = entity_manager.create_system<HudSystem>(memecity::engine::ecs::System::draw, _hud);
	FightingSystem* system = dynamic_cast<FightingSystem*>(entity_manager.get_system_of_type<FightingSystem>());

	memecity::engine::ecs::eventing::bind(system->health_event, &hud_system, &HudSystem::on_health_changed);

	_hud.create_overlay_item("HEALTH", "Health:100", 16, 100, 20);
	_hud.create_overlay_item("SCORE", "Score:100", 16, 100, 40);
	_hud.create_overlay_item("EXP", "Exp:100", 16, 100, 60);
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
	_context->get_multimedia_manager().play_background_music("Music/bgm-game.mp3", 100);
}

void GameState::on_exit()
{
	_context->get_multimedia_manager().pause_background_music();
}
