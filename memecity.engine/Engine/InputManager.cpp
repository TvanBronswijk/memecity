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

	bool InputManager::is_pressed(std::string key)
	{
		auto it = _is_pressed.find(key);
		if (it == _is_pressed.end()) {
			_is_pressed[key] = input_facade->is_down(key);
		}
		else {
			if (input_facade->is_down(key)) {
				if (it->second) {
					return false;
				}
				else {
					it->second = input_facade->is_down(key);
				}
			}
			else {
				it->second = input_facade->is_down(key);
			}
		}
		return _is_pressed[key];
	}

	bool InputManager::is_down(std::string key) const
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
