#ifndef _GAME_INPUT_H
#define _GAME_INPUT_H

namespace input {
	using Key = const char*;
	
	static constexpr Key UP = "W";
	static constexpr Key DOWN = "S";
	static constexpr Key LEFT = "A";
	static constexpr Key RIGHT = "D";
	static constexpr Key ATTACK = "Space";
	static constexpr Key INTERACTION = "E";
	static constexpr Key ESCAPE = "Escape";
	static constexpr Key ENTER = "Return";
};

#endif
