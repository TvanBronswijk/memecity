﻿#include "Color.h"

namespace memecity::engine::sdl {
	Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		sdl_color = { r, g, b , a };
	}

	SDL_Color Color::get_sdl_color() const
	{
		return sdl_color;
	}
}
