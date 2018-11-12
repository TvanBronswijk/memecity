#ifndef _RAW__FONT_WRAPPER_H
#define _RAW__FONT_WRAPPER_H
#include <SDL_ttf.h>

class RawFontWrapper
{
private:
	TTF_Font* font;
public:
	RawFontWrapper()
		: font(nullptr) {}

	RawFontWrapper(TTF_Font* font)
		: font(font) {}

	~RawFontWrapper()
	{
		TTF_CloseFont(font);
	}

	TTF_Font* get() const
	{
		return font;
	}
	TTF_Font* operator->() const
	{
		return font;
	}
	TTF_Font* operator*() const
	{
		return font;
	}
};

#endif