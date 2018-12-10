#include "GameState.h"
#include "../../Assets.h"
#include "../Systems/FightingSystem.h"
#include "../Systems/ExpSystem.h"

GameState::GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc,
	memecity::engine::ecs::EntityManager em) : _context(&gc), entity_manager(std::move(em)), State(sm), _hud(_context->get_multimedia_manager(), _context->get_multimedia_manager().get_texture(assets::sprites::DARK_BACKGROUND, 0, 0, _context->get_multimedia_manager().get_screen_width(), 100), 0, 0)
{

	auto* system = entity_manager.get_system_of_type<FightingSystem>();

	system->health_changed_event += [&](auto& em, auto args)
	{
		_hud.update("HEALTHVALUE", args.new_health);
	};

	auto* exp_system = entity_manager.get_system_of_type<ExpSystem>();

	exp_system->stats_changed_event += [&](auto& em, auto args)
	{
		_hud.update("S", "S: " + std::to_string(args.s));
		_hud.update("P", "P: " + std::to_string(args.p));
		_hud.update("E", "E: " + std::to_string(args.e));
		_hud.update("C", "C: " + std::to_string(args.c));
		_hud.update("I", "I: " + std::to_string(args.i));
		_hud.update("A", "A: " + std::to_string(args.a));
		_hud.update("L", "L: " + std::to_string(args.l));
	};


	auto& engine = _context->get_engine();
	engine.bindfps([&](bool enabled, auto fps)
	{
		if (enabled) {
			_hud.update("FPS", "FPS: " + std::to_string(fps));
		}else
		{
			_hud.update("FPS", " ");
		}
	});
	

}

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

	_hud.create_overlay_text_item("FPS", " ", 16, 750, 16);
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
	auto& engine = _context->get_engine();
	engine.set_calculate_fps(false);
}
