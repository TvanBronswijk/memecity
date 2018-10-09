#include "Color.h"

/**
 * Creates a new SDL_color based on given RGB values
 */
Color::Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	sdl_color = { r, g, b , a};
}

/**
 * Returns the SDL_Color
 */
SDL_Color Color::get_sdl_color() const
{
	return sdl_color;
}

