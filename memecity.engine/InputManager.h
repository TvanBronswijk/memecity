#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H

#include "InputFacade.h"

class InputManager : public Updatable
{
private:
	std::unique_ptr<InputFacade> input_facade;

public:
	InputManager();
	void update() override;
	bool is_pressed(InputKeys key);
	bool is_quit_pressed();
};

#endif
