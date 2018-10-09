#ifndef _INPUTFACADE_H
#define _INPUTFACADE_H

#include <iostream>
#include "InputKeys.h"
#include "Updatable.h"

class InputFacade : public Updatable
{
private:
	SDL_Event event;
	const Uint8 *state = SDL_GetKeyboardState(nullptr);
	bool quit_pressed = false;

public:
	void update() override;
	bool is_pressed(InputKeys key) const;
	bool is_quit_pressed() const;
};

#endif