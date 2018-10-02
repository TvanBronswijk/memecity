#ifndef _COLOR_H
#define  _COLOR_H
#include <SDL.h>

class Color
{
private :
	SDL_Color sdl_color{};

public:
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	SDL_Color get_sdl_color() const;

};

#endif