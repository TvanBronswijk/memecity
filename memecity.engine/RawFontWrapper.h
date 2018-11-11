#ifndef _RAW__FONT_WRAPPER_H
#define _RAW__FONT_WRAPPER_H
#include <SDL_ttf.h>

class RawFontWrapper
{
private:
	TTF_Font* font = nullptr;
public:
	RawFontWrapper() = default;
	RawFontWrapper(TTF_Font* font);
	~RawFontWrapper();

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