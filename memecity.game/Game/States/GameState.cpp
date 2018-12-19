#include "GameState.h"
#include "LoadingState.h"
#include "../../Assets.h"
#include "../Systems/FightingSystem.h"
#include "../Components/ScoreComponent.h"
#include "Engine/SDL/Wrappers/FileWrapper.h"
#include "../LevelBuilder.h"
#include "../Systems/ExpSystem.h"
#include "../PlayerBuilder.h"
#include "../PlayerManager.h"

void GameState::on_load()
{
	
	Point start;
	next<LoadingState>(*_context, [&](auto& ctx, auto& listener) { start = LevelBuilder(ctx, 128, 128, _load_from_file, _save_location).build(entity_manager, listener); back(); });
	next<LoadingState>(*_context, [&](auto& ctx, auto& listener) { PlayerBuilder(ctx, start).build(entity_manager, listener); back(); });
	if(_load_from_file)
	{
		const auto player_manager = PlayerManager(entity_manager);
		std::string save = assets::saves::SAVE_LOCATION;
		save += "\\" + _save_location + "\\" + assets::saves::SAVE_PLAYER;
		auto& storage = _context->get_storage_manager();
		auto data = storage.load(save);
		if (player_manager.load_player(data));
	}
	
	auto& multimedia_manager = _context->get_multimedia_manager();

	//TODO: Make System Loader
	auto& draw_system = system_pool.create_system<DrawSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& animation_system = system_pool.create_system<AnimationSystem>(memecity::engine::ecs::System::draw, *_context);
	auto& interaction_system = system_pool.create_system<InteractionSystem>(memecity::engine::ecs::System::draw, *_context);
	auto& overlay_system = system_pool.create_system<OverlaySystem>(memecity::engine::ecs::System::draw, multimedia_manager);
	auto& fow_system = system_pool.create_system<FogOfWarSystem>(memecity::engine::ecs::System::draw, multimedia_manager);

	auto& pickpocket_system = system_pool.create_system<PickpocketSystem>(memecity::engine::ecs::System::update, multimedia_manager);
	auto& fighting_system = system_pool.create_system<FightingSystem>(memecity::engine::ecs::System::update, multimedia_manager);
	auto& exp_system = system_pool.create_system<ExpSystem>(memecity::engine::ecs::System::update);
	auto& health_system = system_pool.create_system<HealthSystem>(memecity::engine::ecs::System::update, *_context);
	auto& quest_system = system_pool.create_system<QuestSystem>(memecity::engine::ecs::System::update, multimedia_manager);
	auto& input_system = system_pool.create_system<InputSystem>(memecity::engine::ecs::System::update, *_context, _hud);
	auto& move_system = system_pool.create_system<MoveSystem>();
	auto& collider_system = system_pool.create_system<ColliderSystem>(memecity::engine::ecs::System::update, 256 * 64.0f, 256 * 64.0f);
	auto& ai_system = system_pool.create_system<AISystem>();

	bind(move_system.animated_move_event, &animation_system, &AnimationSystem::on_move);
	bind(input_system.interaction_event, &interaction_system, &InteractionSystem::on_interact);
	bind(input_system.attack_event, &fighting_system, &FightingSystem::on_attack);
	bind(collider_system.collider_event, &move_system, &MoveSystem::on_collision);
	bind(input_system.quest_event, &quest_system, &QuestSystem::on_event);
	bind(fighting_system.damage_event, &health_system, &HealthSystem::on_damage);
	bind(fighting_system.quest_event, &quest_system, &QuestSystem::on_event);
	bind(fighting_system.death_event, &health_system, &HealthSystem::on_death);
	bind(fighting_system.exp_event, &exp_system, &ExpSystem::on_exp_gain);
	bind(pickpocket_system.faulty_pickpocket_event, &interaction_system, &InteractionSystem::on_pickpocket);
	bind(input_system.pickpocket_event, &pickpocket_system, &PickpocketSystem::on_pickpocket);
	bind(pickpocket_system.exp_event, &exp_system, &ExpSystem::on_exp_gain);
	bind(quest_system.exp_event, &exp_system, &ExpSystem::on_exp_gain);

	bind(ai_system.attack_event, &fighting_system, &FightingSystem::on_attack);
	bind(interaction_system.quest_event, &quest_system, &QuestSystem::on_event);
	fighting_system.health_changed_event += [&](auto& em, auto args) { _hud.update("HEALTHVALUE", args.new_health); };
	exp_system.exp_event += [&](auto& em, auto args) {_hud.update("EXP", "Exp/Next: " + std::to_string(args.new_exp) + "/" + std::to_string(args.remaining_exp)); };
	quest_system.blikcoins_event += [&](auto& em, auto args) {_hud.update("BLIKCOIN", "Blikcoins: " + std::to_string(args.new_coin)); };
	pickpocket_system.blikcoins_event += [&](auto& em, auto args) {_hud.update("BLIKCOIN", "Blikcoins: " +  std::to_string(args.new_coin)); };


	fighting_system.health_changed_event += [&](auto& em, auto args) { _hud.update("HEALTHVALUE", args.new_health); };
	
	_hud.create_overlay_text_item("HEALTH", "Health", 16, 100.0f, 20.0f);
	_hud.create_overlay_bar_item("HEALTHVALUE", 100, 20, 150, 12, 100, 200, memecity::engine::sdl::Color(255,0,0), memecity::engine::sdl::Color(0,255,0));
	_hud.create_overlay_text_item("SCORE", "Score:0", 16, 100, 40);
	_hud.create_overlay_text_item("EXP", "Exp:0", 16, 100, 60);

	_hud.create_overlay_text_item("S", "S: 1", 16, 400, 16);
	_hud.create_overlay_text_item("P", "P: 1", 16, 400, 32);
	_hud.create_overlay_text_item("E", "E: 1", 16, 400, 48);
	_hud.create_overlay_text_item("C", "C: 1", 16, 400, 64);
	_hud.create_overlay_text_item("I", "I: 1", 16, 500, 16);
	_hud.create_overlay_text_item("A", "A: 1", 16, 500, 32);
	_hud.create_overlay_text_item("L", "L: 1", 16, 500, 48);

	_hud.create_overlay_text_item("BLIKCOIN", "BlikCoin: 0", 16, 650, 16);

	_hud.create_overlay_text_item("FPS", " ", 16, 750, 48);
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
