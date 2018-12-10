﻿#include "InputFacade.h"

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
		auto it = scancodes.find(key);
		if (it == scancodes.end()) {
			scancodes[key] = SDL_GetScancodeFromName(key.c_str());
			it = scancodes.find(key);
		}
		return state[it->second] != 0;
	}

	bool InputFacade::is_quit_pressed() const
	{
		return quit_pressed;
	}
}
