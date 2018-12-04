#include "InputFacade.h"

namespace memecity::engine::sdl {
	void InputFacade::update()
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT) { quit_pressed = true; }
		}
	}

	bool InputFacade::is_down(std::string key)
	{
		if (scancodes.find(key) == scancodes.end()) {
			scancodes[key] = SDL_GetScancodeFromName(key.c_str());
		}
		return state[scancodes[key]] != 0;
	}

	bool InputFacade::is_quit_pressed() const
	{
		return quit_pressed;
	}
}
