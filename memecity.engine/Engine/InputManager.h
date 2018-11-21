#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
#include "SDL\InputFacade.h"

namespace memecity::engine {
	class InputManager
	{
	private:
		std::unique_ptr<sdl::InputFacade> input_facade;

	public:
		InputManager();
		void update();
		bool is_pressed(sdl::InputKeys key) const;
		bool is_quit_pressed() const;
		void quit();
	};
}

#endif
