﻿#include "TextTexture.h"

namespace memecity::engine::texture {
	TextTexture::TextTexture(std::string text, std::string font_path, int size, const sdl::Color &color, float width, float height) : Texture(font_path, width, height)
	{
		this->text = text;
		this->font_size = size;
		this->color = color;
	}

	std::string TextTexture::get_text() const
	{
		return text;
	}

	void TextTexture::set_text(std::string text)
	{
		this->text = text;
	}


	int TextTexture::get_font_size() const
	{
		return font_size;
	}

	sdl::Color TextTexture::get_color() const
	{
		return color;
	}
}
