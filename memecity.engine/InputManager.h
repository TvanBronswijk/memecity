#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "InputFacade.h"

class InputManager
{

private:
	std::unique_ptr<InputFacade> input_facade;

public:
	InputManager();
	void Update() const;
	bool IsPressed(InputKeys key) const;
	bool IsQuitPressed() const;
};

#endif
