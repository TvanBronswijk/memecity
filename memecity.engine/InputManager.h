#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "InputFacade.h"

class InputManager
{

private:
	std::unique_ptr<InputFacade> input_facade;

public:
	InputManager();
	void update() const;
	bool is_pressed(InputKeys key) const;
	bool is_quit_pressed() const;
};

#endif
