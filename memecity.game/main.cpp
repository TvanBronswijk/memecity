#define _CRTDBG_MAP_ALLOC
#include "GameManager.h"
#include "StateMachine.h"

int main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: ITS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);


	GameManager game_manager;
	return game_manager.run();

	StateMachine state_machine{game_manager};
	state_machine.start();

	return 0;
}
