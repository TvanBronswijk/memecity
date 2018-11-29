#ifndef _MEME_EXCEPTION_BASE_H
#define _MEME_EXCEPTION_BASE_H

#include <iostream>
#include <exception>

namespace memecity::engine::exceptions {
	enum class Level { warning, error };

	class MemeException : public std::exception
	{
	private:
		Level _level;
		const char* _message;
	public:
		MemeException(Level level) : MemeException(level, "An error occured.") {}
		MemeException(Level level, const char* message) : _level(level), _message(message) {}

		const char* message() const throw() {
			return _message;
		}

		Level level() const throw() {
			return _level;
		}
	};
};

#endif
