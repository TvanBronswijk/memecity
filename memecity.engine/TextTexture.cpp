#include "TextTexture.h"

TextTexture::TextTexture(std::string text, std::string font_path, int size, Color &color, int width, int height) : Texture(font_path, width, height)
{
	this->text = text;
	this->font_size = size;
	this->color = color;
}

std::string TextTexture::get_text() const
{
	return text;
}

int TextTexture::get_font_size() const
{
	return font_size;
}

Color TextTexture::get_color() const
{
	return color;
}
