#define _CRTDBG_MAP_ALLOC
#include "GameManager.h"

int main(int argc, char* argv[])
{
#ifdef DEBUG
	//DO NOT DELETE THIS LINE: ITS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	GameManager game_manager;
	return game_manager.run();
}
