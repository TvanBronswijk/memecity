#include "InputFacade.h"

void InputFacade::Update()
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
		default: 
			break;
		}
	}
}

bool InputFacade::IsPressed(const InputKeys key) const
{
	return state[key];
}

bool InputFacade::GetQuitPressed() const
{
	return quitPressed;
}
