#ifndef _COLOR_H
#define  _COLOR_H
#include <SDL.h>

class Color
{
private:
	SDL_Color sdl_color{};

public:
	///<summary>Creates a new SDL_color based on given RGB values.</summary>
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);

	///<summary>Returns the SDL_Color.</summary>
	SDL_Color get_sdl_color() const;
};

#endif