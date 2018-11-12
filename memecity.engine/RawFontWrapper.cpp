#include "RawFontWrapper.h"

RawFontWrapper::RawFontWrapper(TTF_Font* font)
{
	this->font = font;
}

RawFontWrapper::~RawFontWrapper()
{
	TTF_CloseFont(font);
}
