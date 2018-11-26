#ifndef _GAME_STATE_H
#define  _GAME_STATE_H
#include <Engine\State.h>
#include <ECS.h>
#include "..\..\GameManager.h"

struct GameState : public memecity::engine::state::State {
private:
	GameManager::GameContext* _context;
	std::unique_ptr<memecity::engine::ecs::EntityManager> entity_manager;
public:
	GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, std::unique_ptr<memecity::engine::ecs::EntityManager> em)
		: State(sm), _context(&gc), entity_manager(std::move(em)){}
	~GameState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif
