#include "MultimediaManager.h"
#include "Textures\TextTexture.h"
#include "Textures\Texture.h"
#include "SDL\Wrappers\Color.h"

namespace memecity::engine {

	MultimediaManager::MultimediaManager(bool is_fullscreen)
	{
		graphics_facade = std::make_unique<sdl::GraphicsFacade>(is_fullscreen);
		audio_facade = std::make_unique<sdl::AudioFacade>();
		asset_manager = std::make_unique<AssetManager>(*graphics_facade);
		
	}

	bool MultimediaManager::init() const
	{
		if (graphics_facade->init() && audio_facade->init())
		{
			audio_facade->open_audio(44100, 2, 4096);
			return true;
		}

		return false;
	}

	void MultimediaManager::play_background_music(std::string const name, int const volume) const
	{
		auto& music = asset_manager->get_music(name);
		audio_facade->play_background_music(music, volume);
	}

	void MultimediaManager::play_sound_effect(std::string const name, int const repeats, int const volume, int const channel) const
	{
		auto& sound = asset_manager->get_sfx(name);
		audio_facade->play_sound_effect(sound, repeats, volume, channel);
	}

	void MultimediaManager::pause_background_music() const
	{
		audio_facade->pause_background_music();
	}

	void MultimediaManager::clear_graphics() const
	{
		graphics_facade->clear();
	}

	void MultimediaManager::render_texture(texture::Texture &texture) const
	{
		texture.update_render_rect();
		graphics_facade->draw_texture(asset_manager->get_texture(texture.get_filename()), texture.get_render_rect(), (texture.get_is_clipped()) ? &texture.get_clipped_rect() : nullptr);
	}

	void MultimediaManager::render_text_texture(texture::TextTexture& texture) const
	{
		texture.update_render_rect();
		graphics_facade->draw_texture(asset_manager->get_text(texture.get_text(), texture.get_filename(), texture.get_font_size(), texture.get_color().get_sdl_color()), texture.get_render_rect(), nullptr);
	}

	void MultimediaManager::render_graphics() const
	{
		graphics_facade->render();
	}

	std::unique_ptr<texture::Texture> MultimediaManager::get_texture(std::string filename) const
	{
		int width, height;
		auto& sdl_texture = asset_manager->get_texture(filename);
		// Used to determine width and height of the given surface
		SDL_QueryTexture(*sdl_texture, nullptr, nullptr, &width, &height);

		return std::make_unique<texture::Texture>(filename, width, height);
	}

	std::unique_ptr<texture::Texture> MultimediaManager::get_texture(std::string filename, int x, int y, int width, int height) const
	{
		asset_manager->get_texture(filename);

		return std::make_unique<texture::Texture>(filename, x, y, width, height);
	}

	std::unique_ptr<texture::AnimatedTexture> MultimediaManager::get_animated_texture(sdl::TimerFacade &timer, std::string filename, int x, int y, int width, int height, int frame_count, float animation_speed, texture::AnimatedTexture::AnimationDirection direction) const
	{
		asset_manager->get_texture(filename);
		return std::make_unique<texture::AnimatedTexture>(timer, filename, x, y, width, height, frame_count, animation_speed, direction);
	}

	std::unique_ptr<texture::TextTexture> MultimediaManager::get_text_texture(std::string text, std::string font_path, int size, sdl::Color color) const
	{
		int width, height;
		auto& sdl_texture = asset_manager->get_text(text, font_path, size, color.get_sdl_color());
		// Used to determine width and height of the given surface
		SDL_QueryTexture(*sdl_texture, nullptr, nullptr, &width, &height);

		return std::make_unique<texture::TextTexture>(text, font_path, size, color, width, height);
	}

	int MultimediaManager::get_screen_width() const
	{
		return graphics_facade->screen_width;
	}

	int MultimediaManager::get_screen_height() const
	{
		return graphics_facade->screen_height;
	}
}
