#ifndef _INPUTFACADE_H
#define _INPUTFACADE_H

#include <iostream>
#include "InputKeys.h"

class InputFacade
{
private:
	SDL_Event event;
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	bool QuitPressed;
public:
	void update();
	bool isPressed(InputKeys input);
};

#endif