#ifndef _TEXT_TEXTURE
#define _TEXT_TEXTURE
#include "..\SDL\Wrappers\Color.h"
#include "Texture.h"
#include <string>

namespace memecity::engine::texture {
	class TextTexture : public Texture
	{
	private:
		std::string text;
		int font_size = 0;
		sdl::Color color{ 0,0,0 };
	public:
		TextTexture(std::string text, std::string font_path, int size, const sdl::Color &color, int width, int height);
		std::string get_text() const;
		void set_text(std::string text);
		int get_font_size() const;
		sdl::Color get_color() const;
	};
}

#endif
