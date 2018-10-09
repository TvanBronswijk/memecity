#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <SDL.h>
#include "GameObject.h"

class Texture : public GameObject
{
protected:
	SDL_Texture* texture;
	std::shared_ptr<GraphicsFacade> graphics_facade;
	bool is_clipped;

	int texture_width;
	int texture_height;

	SDL_Rect render_rect;
	SDL_Rect clipped_rect;

public:
	Texture(std::shared_ptr<GraphicsFacade> graphics_facade, SDL_Texture* texture);
	Texture(std::shared_ptr<GraphicsFacade> graphics_facade, SDL_Texture* texture, int x, int y, int width, int height);
	~Texture();

	void render() override;
};

#endif