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

	bool InputManager::is_pressed(sdl::InputKeys key)
	{
		if (_is_pressed.find(key) == _is_pressed.end()) {
			_is_pressed[key] = input_facade->is_down(key);
		}
		else {
			if (input_facade->is_down(key)) {
				if (_is_pressed.at(key)) {
					return false;
				}
				else {
					_is_pressed[key] = input_facade->is_down(key);
				}
			}
			else {
				_is_pressed[key] = input_facade->is_down(key);
			}
		}
		return _is_pressed.at(key);
	}

	bool InputManager::is_down(sdl::InputKeys key) const
	{
		return input_facade->is_down(key);
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
