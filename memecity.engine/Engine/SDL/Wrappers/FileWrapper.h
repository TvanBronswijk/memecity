#ifndef _RW_OPS_WRAPPER_H
#define _RW_OPS_WRAPPER_H
#include <SDL.h>

namespace memecity::engine::sdl {

	enum Mode { r, w, a };

	class FileWrapper
	{
	private:
		SDL_RWops *_rw_ops;

	public:
		FileWrapper()
			: _rw_ops(nullptr) {}

		FileWrapper(const char* file_name, const Mode mode)
		{
			switch (mode)
			{
			case r:
				_rw_ops = SDL_RWFromFile(file_name, "r");
				break;
			case w:
				_rw_ops = SDL_RWFromFile(file_name, "w");
				break;
			case a:
				_rw_ops = SDL_RWFromFile(file_name, "a");
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
			return _rw_ops;
		}

		SDL_RWops* operator->() const
		{
			return _rw_ops;
		}

		SDL_RWops* operator*() const
		{
			return _rw_ops;
		}
	};
}
#endif