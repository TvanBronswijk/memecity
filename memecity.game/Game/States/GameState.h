#ifndef _GAME_STATE_H
#define  _GAME_STATE_H
#include <Engine\State.h>
#include <ECS.h>
#include "..\Systems.h"
#include "..\..\GameManager.h"

struct GameState : public memecity::engine::state::State {
private:
	GameManager::GameContext* _context;
	memecity::engine::ecs::EntityManager entity_manager;
	memecity::engine::ecs::SystemPool system_pool;
public:
	GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, memecity::engine::ecs::EntityManager em)
		: State(sm), _context(&gc), entity_manager(std::move(em)){
		auto& multimedia_manager = _context->get_multimedia_manager();

		auto& draw_system = system_pool.create_system<DrawSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
		auto& animation_system = system_pool.create_system<AnimationSystem>(memecity::engine::ecs::System::draw, *_context);
		auto& input_system = system_pool.create_system<InputSystem>(memecity::engine::ecs::System::update, *_context);
		auto& move_system = system_pool.create_system<MoveSystem>();
		auto& collider_system = system_pool.create_system<ColliderSystem>();
		auto& ai_system = system_pool.create_system<AISystem>();
		auto& fighting_system = system_pool.create_system<FightingSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
		auto& interaction_system = system_pool.create_system<InteractionSystem>(memecity::engine::ecs::System::draw, multimedia_manager);
		auto& overlay_system = system_pool.create_system<OverlaySystem>(memecity::engine::ecs::System::draw, multimedia_manager);

		memecity::engine::ecs::eventing::bind(move_system.animated_move_event, &animation_system, &AnimationSystem::on_move);
		memecity::engine::ecs::eventing::bind(input_system.interaction_event, &interaction_system, &InteractionSystem::on_interact);
		memecity::engine::ecs::eventing::bind(input_system.attack_event, &fighting_system, &FightingSystem::on_attack);
		memecity::engine::ecs::eventing::bind(collider_system.collider_event, &move_system, &MoveSystem::on_collision);
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
