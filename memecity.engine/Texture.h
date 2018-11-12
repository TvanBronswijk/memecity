#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GameObject.h"
#include "Rectangle.h"
#include <string>

class Texture : public GameObject
{
protected:
	std::string filename;
	bool is_clipped;

	int texture_width;
	int texture_height;

	Rectangle render_rect;
	Rectangle clipped_rect;

public:
	Texture(std::string filename, int width, int height);
	Texture(std::string filename, int x, int y, int width, int height);
	void update_render_rect();
	bool get_is_clipped() const;
	Rectangle get_render_rect() const;
	Rectangle get_clipped_rect() const;
	std::string get_filename() const;
};

#endif