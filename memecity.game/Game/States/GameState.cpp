#include "GameState.h"
#include "LoadingState.h"
#include "../../Assets.h"
#include "../Systems/FightingSystem.h"
#include "..\GameLoader.h"

void GameState::on_load()
{
	next<LoadingState>(*_context, [&](auto& ctx, auto& listener) { GameLoader(ctx, 256, 256).build(entity_manager, listener); back(); });

	auto& multimedia_manager = _context->get_multimedia_manager();

	//TODO: Make System Loader
	auto& draw_system = system_pool.create_system<DrawSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& animation_system = system_pool.create_system<AnimationSystem>(memecity::engine::ecs::System::draw, *_context);
	auto& fighting_system = system_pool.create_system<FightingSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& interaction_system = system_pool.create_system<InteractionSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& overlay_system = system_pool.create_system<OverlaySystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& fow_system = system_pool.create_system<FogOfWarSystem>(memecity::engine::ecs::System::draw, multimedia_manager);

	auto& input_system = system_pool.create_system<InputSystem>(memecity::engine::ecs::System::update, *_context);
	auto& move_system = system_pool.create_system<MoveSystem>();
	auto& collider_system = system_pool.create_system<ColliderSystem>(memecity::engine::ecs::System::update, 256 * 64.0f, 256 * 64.0f);
	auto& ai_system = system_pool.create_system<AISystem>();

	memecity::engine::ecs::eventing::bind(move_system.animated_move_event, &animation_system, &AnimationSystem::on_move);
	memecity::engine::ecs::eventing::bind(input_system.interaction_event, &interaction_system, &InteractionSystem::on_interact);
	memecity::engine::ecs::eventing::bind(input_system.attack_event, &fighting_system, &FightingSystem::on_attack);
	memecity::engine::ecs::eventing::bind(collider_system.collider_event, &move_system, &MoveSystem::on_collision);
	fighting_system.health_changed_event += [&](auto& em, auto args) { _hud.update("HEALTHVALUE", args.new_health); };
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
