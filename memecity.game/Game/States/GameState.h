#ifndef _GAME_STATE_H
#define  _GAME_STATE_H
#include <Engine\State.h>
#include <ECS.h>
#include "..\..\GameManager.h"
#include "UI/Overlay/Overlay.h"

struct GameState : public memecity::engine::state::State {
private:
	GameManager::GameContext* _context;
	memecity::engine::ecs::EntityManager entity_manager;
	memecity::engine::ui::overlay::Overlay _hud;
public:
	GameState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc, memecity::engine::ecs::EntityManager em);
		
	~GameState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif
