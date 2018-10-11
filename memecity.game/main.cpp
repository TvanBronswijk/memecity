#define _CRTDBG_MAP_ALLOC
#include <memory>
#include "GameManager.h"

int main(int argc, char* argv[])
{	 
	//DO NOT DELETE THIS LINE: ITS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::unique_ptr<GameManager> gameManager = std::make_unique<GameManager>();
	return gameManager->run();
}