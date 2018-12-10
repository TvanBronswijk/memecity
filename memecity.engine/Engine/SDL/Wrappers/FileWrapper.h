#ifndef _RW_OPS_WRAPPER_H
#define _RW_OPS_WRAPPER_H
#include <SDL.h>

namespace memecity::engine::sdl {

	enum Mode { r, w, a };

	class FileWrapper
	{
	private:
		SDL_RWops *rw_ops;

	public:
		FileWrapper()
			: rw_ops(nullptr) {}

		FileWrapper(const char* file_name, const Mode mode)
		{
			switch (mode)
			{
			case r:
				rw_ops = SDL_RWFromFile(file_name, "r");
				break;
			case w:
				rw_ops = SDL_RWFromFile(file_name, "w");
				break;
			case a:
				rw_ops = SDL_RWFromFile(file_name, "a");
				break;
			default:
				break;
			}
		}

		~FileWrapper()
		{
		}

		SDL_RWops* get() const
		{
			return rw_ops;
		}

		SDL_RWops* operator->() const
		{
			return rw_ops;
		}

		SDL_RWops* operator*() const
		{
			return rw_ops;
		}
	};
}
#endif