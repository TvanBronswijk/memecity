#include "MultimediaManager.h"
#include "Textures\TextTexture.h"
#include "Textures\Texture.h"
#include "SDL\Wrappers\Color.h"

namespace memecity::engine {
	bool MultimediaManager::init()
	{
		if (graphics_facade.init() && audio_facade.init())
		{
			audio_facade.open_audio(44100, 2, 4096);
			return true;
		}
		return false;
	}

	void MultimediaManager::play_background_music(std::string name, int volume)
	{
		auto& music = asset_manager.get_music(name);
		audio_facade.stop_background_music();
		audio_facade.play_background_music(music, volume);
	}

	void MultimediaManager::pause_background_music() const
	{
		audio_facade.pause_background_music();
	}

	void MultimediaManager::play_sound_effect(std::string name, int repeats, int channel, int volume)
	{
		auto& sound = asset_manager.get_sfx(name);
		audio_facade.play_sound_effect(sound, repeats, volume, channel);
	}

	void MultimediaManager::render_graphics() const
	{
		graphics_facade.render();
	}

	void MultimediaManager::clear_graphics() const
	{
		graphics_facade.clear();
	}

	void MultimediaManager::render_texture(texture::Texture &texture)
	{
		texture.update_render_rect();
		graphics_facade.draw_texture(asset_manager.get_texture(texture.get_filename()), texture.get_render_rect(), (texture.get_is_clipped()) ? &texture.get_clipped_rect() : nullptr);
	}

	void MultimediaManager::render_texture(float x, float y, texture::Texture &texture)
	{
		texture.set_position({x, y});
		render_texture(texture);
	}

	void MultimediaManager::render_texture(float x, float y, std::string filename)
	{
		auto texture = get_texture(filename);
		render_texture(x, y, *texture);
	}

	void MultimediaManager::render_texture(float x, float y, std::string filename, uRectangle<int> clipped_rect)
	{
		auto texture = get_texture(filename, clipped_rect);
		render_texture(x, y, *texture);
	}

	void MultimediaManager::render_texture(float x, float y, std::string filename, uRectangle<int> clipped_rect, int frame_count, float animation_speed, texture::AnimatedTexture::AnimationDirection direction)
	{
		auto texture = get_texture(filename, clipped_rect, frame_count, animation_speed, direction);
		render_texture(x, y, *texture);
	}

	void MultimediaManager::render_text(texture::TextTexture& texture)
	{
		texture.update_render_rect();
		graphics_facade.draw_texture(asset_manager.get_text(texture.get_text(), texture.get_filename(), texture.get_font_size(), texture.get_color().get_sdl_color()), texture.get_render_rect(), nullptr);
	}

	void MultimediaManager::render_text(float x, float y, texture::TextTexture& texture)
	{
		texture.set_position({x, y});
		render_text(texture);
	}

	void MultimediaManager::render_text(float x, float y, std::string text, int size, sdl::Color color)
	{
		auto text_texture = get_text(text, size, color);
		render_text(x, y, *text_texture);
	}

	void MultimediaManager::render_text(float x, float y, std::string font_path, std::string text, int size, sdl::Color color)
	{
		auto text_texture = get_text(font_path, text, size, color);
		render_text(x, y, *text_texture);
	}

	std::unique_ptr<texture::Texture> MultimediaManager::get_texture(std::string filename)
	{
		int width, height;
		auto& sdl_texture = asset_manager.get_texture(filename);
		graphics_facade.get_dimensions(sdl_texture, width, height);
		return std::make_unique<texture::Texture>(filename, width, height);
	}

	std::unique_ptr<texture::Texture> MultimediaManager::get_texture(std::string filename, int clipped_x, int clipped_y, int clipped_w, int clipped_h)
	{
		asset_manager.get_texture(filename);
		return std::make_unique<texture::Texture>(filename, clipped_x, clipped_y, clipped_w, clipped_h);
	}

	std::unique_ptr<texture::Texture> MultimediaManager::get_texture(std::string filename, uRectangle<int> clipped_rect)
	{
		return get_texture(filename, clipped_rect.x, clipped_rect.y, clipped_rect.w, clipped_rect.h);
	}

	std::unique_ptr<texture::AnimatedTexture> MultimediaManager::get_texture(std::string filename, int clipped_x, int clipped_y, int clipped_w, int clipped_h, int frame_count, float animation_speed, texture::AnimatedTexture::AnimationDirection direction)
	{
		asset_manager.get_texture(filename);
		return std::make_unique<texture::AnimatedTexture>(filename, clipped_x, clipped_y, clipped_w, clipped_h, frame_count, animation_speed, direction);
	}

	std::unique_ptr<texture::AnimatedTexture> MultimediaManager::get_texture(std::string filename, uRectangle<int> clipped_rect, int frame_count, float animation_speed, texture::AnimatedTexture::AnimationDirection direction)
	{
		return get_texture(filename, clipped_rect.x, clipped_rect.y, clipped_rect.w, clipped_rect.h, frame_count, animation_speed, direction);
	}

	void MultimediaManager::set_default_font(std::string font, int size)
	{
		asset_manager.get_font(font, size);
		default_font = font;
	}

	std::string MultimediaManager::get_default_font() const
	{
		return default_font;
	}

	std::unique_ptr<texture::TextTexture> MultimediaManager::get_text(std::string text, int size, sdl::Color color)
	{
		return get_text(default_font, text, size, color);
	}

	std::unique_ptr<texture::TextTexture> MultimediaManager::get_text(std::string font_path, std::string text, int size, sdl::Color color)
	{
		int width, height;
		auto& sdl_texture = asset_manager.get_text(text, font_path, size, color.get_sdl_color());
		graphics_facade.get_dimensions(sdl_texture, width, height);
		return std::make_unique<texture::TextTexture>(text, font_path, size, color, width, height);
	}

	int MultimediaManager::get_screen_width() const
	{
		return graphics_facade.screen_width;
	}

	int MultimediaManager::get_screen_height() const
	{
		return graphics_facade.screen_height;
	}

	void MultimediaManager::set_fullscreen(bool fullscreen_enabled)
	{
		graphics_facade.set_fullscreen(fullscreen_enabled);
	}
	bool MultimediaManager::is_fullscreen() const
	{
		return graphics_facade.get_fullscreen();
	}
}
