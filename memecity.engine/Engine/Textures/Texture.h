#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameObject.h"
#include "..\Util\Rectangle.h"
#include <string>

namespace memecity::engine::texture {
	class Texture : public GameObject
	{
	protected:
		std::string filename;
		bool is_clipped;

		float texture_width;
		float texture_height;

		Rectangle render_rect;
		Rectangle clipped_rect;

	public:
		Texture(std::string filename, float width, float height);
		Texture(std::string filename, float x, float y, float width, float height);
		void update_render_rect();
		bool get_is_clipped() const;
		Rectangle get_render_rect() const;
		Rectangle get_clipped_rect() const;
		std::string get_filename() const;
	};
}

#endif
