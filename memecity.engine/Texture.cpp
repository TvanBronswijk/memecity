#include "Texture.h"

Texture::Texture(std::shared_ptr<MultimediaManager> multimediaManager, const std::string filename)
{
	multimedia_manager = multimediaManager;
	texture = multimedia_manager->GetTexture(filename);
	SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);

	is_clipped = false;

	render_rect.w = texture_width;
	render_rect.h = texture_height;
}

Texture::Texture(std::shared_ptr<MultimediaManager> multimediaManager, const std::string filename, const int x, const int y, const int width, int height)
{
	multimedia_manager = multimediaManager;
	texture = multimedia_manager->GetTexture(filename);
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

Texture::Texture(std::shared_ptr<MultimediaManager> multimediaManager, const std::string text, const std::string font_path, const int size, const SDL_Color color)
{
	multimedia_manager = multimediaManager;
	texture = multimedia_manager->GetText(text, font_path, size, color);

	is_clipped = false;

	SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);

	render_rect.w = texture_width;
	render_rect.h = texture_height;
}

Texture::~Texture()
{
	texture = nullptr;
}

void Texture::Render()
{
	const auto pos = Pos(world);
	render_rect.x = int(pos.x - texture_width * 0.5f);
	render_rect.y = int(pos.y - texture_height * 0.5f);
	multimedia_manager->DrawTexture(texture, (is_clipped) ? &clipped_rect : nullptr, &render_rect);
}