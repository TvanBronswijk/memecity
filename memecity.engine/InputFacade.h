#ifndef _INPUTFACADE_H
#define _INPUTFACADE_H

#include <iostream>
#include "InputKeys.h"

class InputFacade
{
private:
	SDL_Event event;
	const std::uint8_t *state = SDL_GetKeyboardState(nullptr);
	bool quit_pressed = false;

public:
	///<summary>Updates the Keyboard State to find out which keys are pressed.</summary>
	void update();

	///<summary>Returns if a given key is pressed.</summary>
	bool is_pressed(InputKeys key) const;

	///<summary>Returns whether quit is pressed.</summary>
	bool is_quit_pressed() const;
};

#endif