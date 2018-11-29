#ifndef _MEME_EXCEPTION_SDL_H
#define _MEME_EXCEPTION_SDL_H
#include "MemeException.h"

namespace memecity::engine::exceptions {
	class SDLException : public MemeException
	{
	public:
		SDLException() : SDLException("The SDL library is unable to load.") {}
		SDLException(const char* message) : SDLException(Level::error, message) {}
		SDLException(Level level, const char* message) : MemeException(level, message) {}
	};
}

#endif
