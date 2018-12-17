#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include <Engine.h>

class GameManager : public memecity::engine::MemeEngine
{
private:
	memecity::engine::state::StateManager _states;
public:
	GameManager() : MemeEngine() {
		_context = std::make_unique<GameContext>(*this);
	}

	struct GameContext : public memecity::engine::MemeEngine::Context {
	private:
		memecity::engine::state::StateManager* state_manager;
	public:
		GameContext(memecity::engine::MultimediaManager& mm, memecity::engine::InputManager& im, memecity::engine::sdl::TimerFacade& t, memecity::engine::state::StateManager& sm, memecity::engine::StorageManager& stm, MemeEngine& engine)
			: Context(mm, im, t, stm, engine), state_manager(&sm) {}
		GameContext(GameManager& engine)
			: Context(engine), state_manager(&engine._states) {}
		memecity::engine::state::StateManager& get_state_manager() { return *state_manager; }
	};
	void init() override;
	void update(float dt) override;
	void draw() override;
	GameContext& get_context() { return *(dynamic_cast<GameContext*>(_context.get())); }
};


#endif
