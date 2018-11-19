
#include "State.h"
#ifndef STATE_MACHINE
#include "GameManager.h"
#define _GAME_MANAGER_H


class StateMachine
{
public:
	StateMachine(GameManager& game_manager)
	: _gamemanager(game_manager),state(starting){};
	void start();
private:
	GameManager& _gamemanager;
	State state;
};

#endif