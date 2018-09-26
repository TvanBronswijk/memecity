#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Texture.h"

int main(int argc, char* argv[])
{
	//DO NOT DELETE THIS LINE: IS INTENDED TO FIND MEMORY LEAKS
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Graphics *graphics = Graphics::Instance();

	Texture *tex = new Texture("memecity", "PressStart2P.ttf", 50, {0, 0, 0});
	tex->Pos(Vector2(Graphics::SCREEN_WIDTH * 0.5f, 80));

	while (1) {
		graphics->ClearBackBuffer();
		tex->Render();
		graphics->Render();
	}

	return 0;
}
