#ifndef _INPUTFACADE_H
#define _INPUTFACADE_H

#include <iostream>
#include "InputKeys.h"

class InputFacade
{
private:
	SDL_Event event;
	const Uint8 *state = SDL_GetKeyboardState(nullptr);
	bool quitPressed = false;
public:
	void Update();
	bool IsPressed(InputKeys input) const;
	bool GetQuitPressed() const;
};

#endif