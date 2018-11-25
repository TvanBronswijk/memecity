#ifndef _GAME_LOADING_STATE_H
#define  _GAME_LOADING_STATE_H
#include <Engine\State.h>
#include "..\..\GameManager.h"
#include "..\GameLoader.h"

struct GameLoadingState : public memecity::engine::state::State {
private:
	GameManager::GameContext* _context;
	GameLoader game_loader;
public:
	GameLoadingState(memecity::engine::state::StateManager& sm, GameManager::GameContext& gc)
		: State(sm), game_loader(gc, 64, 64), _context(&gc)  {}
	~GameLoadingState() = default;
	void on_load() override;
	void update(float dt) override;
	void draw() override;
	void on_enter() override;
	void on_exit() override;
	GameManager::GameContext& get_context() { return *_context; }
};

#endif
