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
	static constexpr Key DROP = "R";
	static constexpr Key TAKE = "F";
	static constexpr Key ESCAPE = "Escape";
	static constexpr Key ENTER = "Return";
	static constexpr Key N = "N";
	static constexpr Key DEVELOPER = "`";
	static constexpr Key Z = "Z";
	static constexpr Key ONE = "1";
	static constexpr Key TWO = "2";
	static constexpr Key STATS = "P";
	static constexpr Key THREE = "3";
	static constexpr Key ARROWDOWN = "Down";
	static constexpr Key ARROWUP = "Up";
	static constexpr Key SPEEDUP = "PageUp";
	static constexpr Key SPEEDDOWN = "PageDown";
	static constexpr Key SPEEDRESET = "Home";
};

#endif
