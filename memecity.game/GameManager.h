#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include <Engine.h>

class GameManager : public memecity::engine::MemeEngine
{
private:
	memecity::engine::state::StateContext _context{ *this };
	memecity::engine::state::StateMachine _states{};

	protected:
	void init() override;
	void update(float dt) override;
	void draw() override;
};


#endif
