#include "Texture.h"

namespace memecity::engine::texture {
	Texture::Texture(std::string filename, int width, int height)
	{
		this->filename = filename;
		is_clipped = false;

		texture_width = width;
		texture_height = height;

		render_rect.w = texture_width;
		render_rect.h = texture_height;
	}

	Texture::Texture(std::string filename, int x, int y, int width, int height)
	{
		this->filename = filename;
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

	void Texture::update_render_rect()
	{
		const auto pos = get_position(world);
		render_rect.x = int(pos.x - texture_width * 0.5f);
		render_rect.y = int(pos.y - texture_height * 0.5f);
	}

	bool Texture::get_is_clipped() const
	{
		return is_clipped;
	}

	Rectangle Texture::get_render_rect() const
	{
		return render_rect;
	}

	Rectangle Texture::get_clipped_rect() const
	{
		return clipped_rect;
	}

	std::string Texture::get_filename() const
	{
		return filename;
	}
}
