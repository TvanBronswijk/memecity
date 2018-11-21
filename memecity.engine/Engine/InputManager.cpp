#include "InputManager.h"

namespace memecity::engine {
	InputManager::InputManager()
	{
		input_facade = std::make_unique<sdl::InputFacade>();
	}

	void InputManager::update()
	{
		input_facade->update();
	}

	bool InputManager::is_pressed(sdl::InputKeys key) const
	{
		return input_facade->is_pressed(key);
	}

	bool InputManager::is_quit_pressed() const
	{
		return input_facade->is_quit_pressed();
	}

	void InputManager::quit()
	{
		input_facade->quit();
	}
}
