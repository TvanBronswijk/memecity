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
		std::map<sdl::InputKeys, bool> _is_pressed{};
	public:
		InputManager();
		void update();
		bool is_pressed(sdl::InputKeys key);
		bool is_down(sdl::InputKeys key) const;
		bool is_quit_pressed() const;
		void quit();
	};
}

#endif
