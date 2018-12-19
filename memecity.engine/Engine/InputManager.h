#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include <memory>
#include <map>
#include "SDL\InputFacade.h"


namespace memecity::engine {
	class InputManager
	{
	private:
		std::unique_ptr<sdl::InputFacade> input_facade;
		std::map<std::string, bool> _is_pressed{};
	public:
		InputManager();
		void update();
		bool is_pressed(std::string key);
		bool is_down(std::string key) const;
		bool is_quit_pressed() const;
		void enable_text_editing();
		void disable_text_editing();
		std::string get_text();
		void quit();
	};
}

#endif
