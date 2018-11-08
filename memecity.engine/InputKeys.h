#ifndef _INPUTKEYS_H
#define _INPUTKEYS_H
#include <SDL.h>

/**
 * Abstraction of the SDL Scancodes
 */
const enum InputKeys
{
	Up = SDL_SCANCODE_W,
	Down = SDL_SCANCODE_S,
	Left = SDL_SCANCODE_A,
	Right = SDL_SCANCODE_D,
	Interaction = SDL_SCANCODE_E,
	One = SDL_SCANCODE_1,
	Two = SDL_SCANCODE_2,
	Three = SDL_SCANCODE_3,
	Four = SDL_SCANCODE_4,
	Five = SDL_SCANCODE_5,
	Six = SDL_SCANCODE_6,
	Inventory = SDL_SCANCODE_TAB,
	Attack = SDL_SCANCODE_SPACE,
	Escape = SDL_SCANCODE_ESCAPE
};

#endif