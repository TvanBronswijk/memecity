#ifndef _RAW_WINDOW_WRAPPER_H
#define _RAW_WINDOW_WRAPPER_H
#include <SDL.h>

namespace memecity::engine::sdl {
	class RawWindowWrapper
	{
	private:
		SDL_Window* window;

	public:
		RawWindowWrapper()
			: window(nullptr) {}

		RawWindowWrapper(SDL_Window* win)
			: window(win) {}

		~RawWindowWrapper()
		{
			SDL_DestroyWindow(window);
		}

		SDL_Window* get() const
		{
			return window;
		}
		SDL_Window* operator->() const
		{
			return window;
		}
		SDL_Window* operator*()  const
		{
			return window;
		}
	};
}

#endif
