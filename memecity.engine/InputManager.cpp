#include "InputManager.h"

InputManager::InputManager()
{
	input_facade = std::make_unique<InputFacade>();
}

void InputManager::update()
{
	input_facade->update();
}

bool InputManager::is_pressed(const InputKeys key) const
{
	return input_facade->is_pressed(key);
}

bool InputManager::is_quit_pressed() const
{
	return input_facade->is_quit_pressed();
}