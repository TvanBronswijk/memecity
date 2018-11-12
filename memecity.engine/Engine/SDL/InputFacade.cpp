#include "InputFacade.h"

namespace memecity::engine::sdl {
	void InputFacade::update()
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT) { quit_pressed = true; }
			state = SDL_GetKeyboardState(nullptr);
		}
	}

	bool InputFacade::is_pressed(InputKeys key) const
	{
		return state[key] != 0;
	}

	bool InputFacade::is_quit_pressed() const
	{
		return quit_pressed;
	}
}
