#include "InputManager.h"

InputManager::InputManager()
{
	input_facade = std::make_unique<InputFacade>();
}

void InputManager::Update() const
{
	input_facade->Update();
}

bool InputManager::IsPressed(const InputKeys key) const
{
	return input_facade->IsPressed(key);
}

bool InputManager::IsQuitPressed() const
{
	return input_facade->IsQuitPressed();
}