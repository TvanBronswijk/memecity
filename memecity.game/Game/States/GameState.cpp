#include "GameState.h"
#include "LoadingState.h"
#include "../../Assets.h"
#include "../Systems/FightingSystem.h"
#include "../GameLoader.h"
#include "../Systems/ExpSystem.h"

void GameState::on_load()
{
	next<LoadingState>(*_context, [&](auto& ctx, auto& listener) { GameLoader(ctx, 128, 128).build(entity_manager, listener); back(); });

	auto& multimedia_manager = _context->get_multimedia_manager();

	//TODO: Make System Loader
	auto& draw_system = system_pool.create_system<DrawSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& animation_system = system_pool.create_system<AnimationSystem>(memecity::engine::ecs::System::draw, *_context);
	auto& fighting_system = system_pool.create_system<FightingSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& interaction_system = system_pool.create_system<InteractionSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& overlay_system = system_pool.create_system<OverlaySystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& fow_system = system_pool.create_system<FogOfWarSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	
	auto& exp_system = system_pool.create_system<ExpSystem>();
	auto& input_system = system_pool.create_system<InputSystem>(memecity::engine::ecs::System::update, *_context);
	auto& move_system = system_pool.create_system<MoveSystem>();
	auto& collider_system = system_pool.create_system<ColliderSystem>(memecity::engine::ecs::System::update, 256 * 64.0f, 256 * 64.0f);
	auto& ai_system = system_pool.create_system<AISystem>();

	bind(move_system.animated_move_event, &animation_system, &AnimationSystem::on_move);
	bind(input_system.interaction_event, &interaction_system, &InteractionSystem::on_interact);
	bind(input_system.attack_event, &fighting_system, &FightingSystem::on_attack);
	bind(collider_system.collider_event, &move_system, &MoveSystem::on_collision);



	exp_system.stats_changed_event += [&](auto& em, auto args)
	{
		_hud.update("S", "S: " + std::to_string(args.s));
		_hud.update("P", "P: " + std::to_string(args.p));
		_hud.update("E", "E: " + std::to_string(args.e));
		_hud.update("C", "C: " + std::to_string(args.c));
		_hud.update("I", "I: " + std::to_string(args.i));
		_hud.update("A", "A: " + std::to_string(args.a));
		_hud.update("L", "L: " + std::to_string(args.l));
	};

	fighting_system.health_changed_event += [&](auto& em, auto args) { _hud.update("HEALTHVALUE", args.new_health); };

	auto& engine = _context->get_engine();
	engine.bind_fps([&](bool enabled, auto fps)
	{
		if (enabled) {
			_hud.update("FPS", "FPS: " + std::to_string(fps));
		}else
		{
			_hud.update("FPS", " ");
		}
	});

	engine.bind_game_speed([&](bool enabled, float game_speed)
	{
		if(enabled)
		{
			_hud.update("GAMESPEED", "Gamespeed: " + std::to_string(game_speed));
		}else
		{
			_hud.update("GAMESPEED", " ");
		}
	});
	
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
	_hud.create_overlay_text_item("GAMESPEED", " ", 16, 750, 32);
}

void GameState::update(float dt)
{
	system_pool.update(entity_manager, dt, memecity::engine::ecs::System::update);
}

void GameState::draw()
{
	system_pool.update(entity_manager, 0.0f, memecity::engine::ecs::System::draw);
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
