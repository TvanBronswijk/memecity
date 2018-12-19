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
			it = _is_pressed.find(key);
		}
		else {
			bool key_is_down = input_facade->is_down(key);
			if (it->second && key_is_down) {
				return false;
			}
			it->second = key_is_down;
		}
		return it->second;
	}

	bool InputManager::is_down(std::string key) const
	{
		return input_facade->is_down(key);
	}

	bool InputManager::is_quit_pressed() const
	{
		return input_facade->is_quit_pressed();
	}

	void InputManager::enable_text_editing()
	{
		input_facade->enable_text_editing();
	}

	void InputManager::disable_text_editing()
	{
		input_facade->disable_text_editing();
	}

	std::string InputManager::get_text()
	{
		return  input_facade->get_text();
	}

	void InputManager::quit()
	{
		input_facade->quit();
	}
}
