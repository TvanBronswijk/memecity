#include "InputFacade.h"

void InputFacade::update()
{
	while (SDL_PollEvent(&event) != 0)
	{
		if (event.type == SDL_QUIT) { quitPressed = true; }
		switch (event.type)
		{
		case SDL_KEYDOWN:
			std::cout << "you have pressed: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
			break;
		case SDL_KEYUP:
			std::cout << "you have released: " << SDL_GetKeyName(event.key.keysym.sym) << std::endl;
			break;
		}
	}
}

bool InputFacade::isPressed(InputKeys key) {
	if (state[key]) {
		return true;
	}
	else return false;
}

bool InputFacade::GetQuitPressed() {
	return quitPressed;
}