#ifndef _INPUTFACADE_H
#define _INPUTFACADE_H
#include <unordered_map>
#include <cstdint>
#include <string>
#include <SDL.h>

namespace memecity::engine::sdl {
	class InputFacade
	{
	private:
		SDL_Event event;
		const std::uint8_t *state = SDL_GetKeyboardState(nullptr);
		std::unordered_map<std::string, SDL_Scancode> scancodes;
		bool quit_pressed = false;

		bool edit_text = false;
		std::string text;
	public:
		///<summary>Updates the Keyboard State to find out which keys are pressed.</summary>
		void update();

		///<summary>Returns if a given key is pressed.</summary>
		bool is_down(std::string key);

		///<summary>Returns whether quit is pressed.</summary>
		bool is_quit_pressed() const;

		void quit()
		{
			quit_pressed = true;
		}

		void enable_text_editing()
		{
			edit_text = true;
			text = "";
			SDL_StartTextInput();
		}
		void disable_text_editing()
		{
			edit_text = false;
			SDL_StopTextInput(); 
		}
		std::string get_text() const
		{
			return text;
		}
	};
}

#endif
