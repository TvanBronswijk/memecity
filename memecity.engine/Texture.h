#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL.h>
#include "Graphic.h"
#include "MultimediaManager.h"

class Texture : public Graphic
{
	protected:
		SDL_Texture* texture;
		std::shared_ptr<MultimediaManager> multimedia_manager;
		bool is_clipped;

		int texture_width;
		int texture_height;

		SDL_Rect render_rect;
		SDL_Rect clipped_rect;

	public:
		Texture(std::shared_ptr<MultimediaManager> multimedia_manager, std::string filename);
		Texture(std::shared_ptr<MultimediaManager> multimedia_manager, std::string filename, int x, int y, int width, int height);
		Texture(std::shared_ptr<MultimediaManager> multimedia_manager, std::string text, std::string font_path, int size, SDL_Color color);
		~Texture();

		virtual void Render();
};

#endif