#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include <Engine.h>

class GameManager : public memecity::engine::MemeEngine
{
private:
	memecity::engine::state::StateMachine _states{memecity::engine::state::StateContext{multimedia_manager, input_manager, *timer}};

	protected:
	void init() override;
	void update(float dt) override;
	void draw() override;
};


#endif
