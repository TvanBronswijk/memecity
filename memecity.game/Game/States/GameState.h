#ifndef _GAME_STATE_H
#define  _GAME_STATE_H
#include <Engine\State.h>
#include <ECS.h>
#include <UI\Overlay\Overlay.h>
#include "..\Systems.h"
#include "..\..\GameManager.h"
#include "..\..\Assets.h"

struct GameState : public memecity::engine::state::State {
private:
	GameManager::GameContext* _context;
	memecity::engine::ecs::EntityManager entity_manager;
	memecity::engine::ecs::SystemPool system_pool;
	memecity::engine::ui::overlay::Overlay _hud;
public:
	GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc)
		: _context(&gc), State(sm), _hud(_context->get_multimedia_manager(), _context->get_multimedia_manager().get_texture(assets::sprites::DARK_BACKGROUND, 0, 0, _context->get_multimedia_manager().get_screen_width(), 100), 0, 0)
	{
		auto& multimedia_manager = _context->get_multimedia_manager();

		auto& draw_system = system_pool.create_system<DrawSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
		auto& animation_system = system_pool.create_system<AnimationSystem>(memecity::engine::ecs::System::draw, *_context);
		auto& fighting_system = system_pool.create_system<FightingSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
		auto& interaction_system = system_pool.create_system<InteractionSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
		auto& overlay_system = system_pool.create_system<OverlaySystem>(memecity::engine::ecs::System::draw, multimedia_manager);

		auto& input_system = system_pool.create_system<InputSystem>(memecity::engine::ecs::System::update, *_context);
		auto& move_system = system_pool.create_system<MoveSystem>();
		auto& collider_system = system_pool.create_system<ColliderSystem>(memecity::engine::ecs::System::update, 256*64.0f, 256*64.0f);
		auto& ai_system = system_pool.create_system<AISystem>();

		memecity::engine::ecs::eventing::bind(move_system.animated_move_event, &animation_system, &AnimationSystem::on_move);
		memecity::engine::ecs::eventing::bind(input_system.interaction_event, &interaction_system, &InteractionSystem::on_interact);
		memecity::engine::ecs::eventing::bind(input_system.attack_event, &fighting_system, &FightingSystem::on_attack);
		memecity::engine::ecs::eventing::bind(collider_system.collider_event, &move_system, &MoveSystem::on_collision);
		fighting_system.health_changed_event += [&](auto& em, auto args) { _hud.update("HEALTHVALUE", args.new_health); };

		_hud.create_overlay_text_item("HEALTH", "Health", 16, 100.0f, 20.0f);
		_hud.create_overlay_bar_item("HEALTHVALUE", 100, 20, 150, 12, 100, 200, memecity::engine::sdl::Color(255, 0, 0), memecity::engine::sdl::Color(0, 255, 0));
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
	~GameState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif
