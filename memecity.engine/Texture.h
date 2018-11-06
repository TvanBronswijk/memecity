#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "GameObject.h"
#include "RectangleFacade.h"

class Texture : public GameObject
{
protected:
	std::string filename;
	bool is_clipped;

	int texture_width = 0;
	int texture_height = 0;

	RectangleFacade render_rect;
	RectangleFacade clipped_rect;

public:
	Texture(std::string filename, int width, int height);
	Texture(std::string filename, int x, int y, int width, int height);
	void update_render_rect();
	bool get_is_clipped() const;
	RectangleFacade get_render_rect() const;
	RectangleFacade get_clipped_rect() const;
	std::string get_filename() const;
};

#endif