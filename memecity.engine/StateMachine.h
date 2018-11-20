#pragma once
#include "State.h"
class GameManager;
namespace memecity::engine {
	class StateMachine
	{
	public:
		StateMachine(GameManager game_manager) : game_manager_(game_manager), state(starting) {};
		void run();
	private:
		GameManager& game_manager_;
		State state;
	};
}
