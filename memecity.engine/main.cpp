#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "GraphicsFacade.h"

int main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: IS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	GraphicsFacade* graphics = new GraphicsFacade();

	delete graphics;

	return 0;
}
