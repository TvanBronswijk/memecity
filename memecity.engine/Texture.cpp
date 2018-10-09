#include "Texture.h"

/**
 * Creates a new instance for a texture based on an entire SDL_Texture
 */
Texture::Texture(std::shared_ptr<GraphicsFacade> graphics_facade, SDL_Texture* texture)
{
	this->graphics_facade = graphics_facade;
	this->texture = texture;

	// Used to determine width and height of texture
	SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);

	is_clipped = false;

	render_rect.w = texture_width;
	render_rect.h = texture_height;
}

/**
 * Creates a new instance for a texture based on a cutout of a SDL_Texture
 */
Texture::Texture(std::shared_ptr<GraphicsFacade> graphics_facade, SDL_Texture* texture, int x, int y, int width, int height)
{
	this->graphics_facade = graphics_facade;
	this->texture = texture;
	is_clipped = true;

	texture_width = width;
	texture_height = height;

	render_rect.w = texture_width;
	render_rect.h = texture_height;

	clipped_rect.x = x;
	clipped_rect.y = y;
	clipped_rect.w = texture_width;
	clipped_rect.h = texture_height;
}

/**
 * Cleanup
 */
Texture::~Texture()
{
	texture = nullptr;
}

/**
 * Delegates rendering the texture
 */
void Texture::render()
{
	const auto pos = get_position(world);
	render_rect.x = int(pos.x - texture_width * 0.5f);
	render_rect.y = int(pos.y - texture_height * 0.5f);
	graphics_facade->draw_texture(texture, (is_clipped) ? &clipped_rect : nullptr, &render_rect);
}
