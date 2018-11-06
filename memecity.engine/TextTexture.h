#ifndef _TEXT_TEXTURE
#define _TEXT_TEXTURE
#include <string>
#include "Color.h"
#include "Texture.h"

class TextTexture : public Texture
{
private:
	std::string text;
	int font_size = 0;
	Color color {0,0,0};
public:
	TextTexture(std::string text, std::string font_path, int size, Color &color, int width, int height);
	std::string get_text() const;
	int get_font_size() const;
	Color get_color() const;
};

#endif
