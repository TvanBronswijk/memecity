#ifndef _MULTIMEDIAMANAGER_H
#define _MULTIMEDIAMANAGER_H
#include <memory>
#include "Textures\AnimatedTexture.h"
#include "SDL\AudioFacade.h"
#include "SDL\GraphicsFacade.h"
#include "AssetManager.h"
#include "Util.h"

namespace memecity::engine {
	namespace sdl {
		class Color;
	};
	namespace texture {
		class TextTexture;
		class Texture;
	};

	class MultimediaManager
	{
	private:
		sdl::AudioFacade audio_facade;
		sdl::GraphicsFacade graphics_facade;
		AssetManager asset_manager;

		std::string default_font;
	public:
		MultimediaManager(bool is_fullscreen)
			: audio_facade(), graphics_facade(is_fullscreen), asset_manager(audio_facade, graphics_facade) {}
		MultimediaManager(AssetManager asset_manager, sdl::AudioFacade audio_facade, sdl::GraphicsFacade graphics_facade)
			: asset_manager(std::move(asset_manager)), audio_facade(std::move(audio_facade)), graphics_facade(std::move(graphics_facade)) {}

		bool init();

		void play_background_music(std::string name, int volume = 100);
		void pause_background_music() const;

		void play_sound_effect(std::string name, int repeats, int channel, int volume = 100);


		void render_graphics() const;
		void clear_graphics() const;

		void render_texture(texture::Texture &texture);
		void render_texture(float x, float y, texture::Texture &texture);
		void render_texture(float x, float y, std::string filename);
		void render_texture(float x, float y, std::string filename, int clipped_x, int clipped_y, int clipped_w, int clipped_h);
		void render_texture(float x, float y, std::string filename, uRectangle<int> clipped_rect);
		void render_texture(float x, float y, std::string filename, int clipped_x, int clipped_y, int clipped_w, int clipped_h, int frame_count, float animation_speed, texture::AnimatedTexture::AnimationDirection direction);
		void render_texture(float x, float y, std::string filename, uRectangle<int> clipped_rect, int frame_count, float animation_speed, texture::AnimatedTexture::AnimationDirection direction);

		void render_rect(float x, float y, float w, float h, bool fill, sdl::Color color = { 255, 255, 255 });
		void render_rect(Rectangle rect, bool fill, sdl::Color color = { 255, 255, 255 });

		void render_text(texture::TextTexture &texture);
		void render_text(float x, float y, texture::TextTexture &texture);
		void render_text(float x, float y, std::string text, int size, sdl::Color color = { 255, 255, 255 });
		void render_text(float x, float y, std::string font_path, std::string text, int size, sdl::Color color = { 255, 255, 255 });

		std::unique_ptr<texture::Texture> get_texture(std::string filename);
		std::unique_ptr<texture::Texture> get_texture(std::string filename, int clipped_x, int clipped_y, int clipped_w, int clipped_h);
		std::unique_ptr<texture::Texture> get_texture(std::string filename, uRectangle<int> clipped_rect);
		std::unique_ptr<texture::AnimatedTexture> get_texture(std::string filename, int clipped_x, int clipped_y, int clipped_w, int clipped_h, int frame_count, float animation_speed, texture::AnimatedTexture::AnimationDirection direction);
		std::unique_ptr<texture::AnimatedTexture> get_texture(std::string filename, uRectangle<int> clipped_rect, int frame_count, float animation_speed, texture::AnimatedTexture::AnimationDirection direction);

		void set_default_font(std::string font, int size = 32);
		std::string get_default_font() const;
		std::unique_ptr<texture::TextTexture> get_text(std::string text, int size, sdl::Color color = {255, 255, 255});
		std::unique_ptr<texture::TextTexture> get_text(std::string font_path, std::string text, int size, sdl::Color color = { 255, 255, 255 });

		int get_screen_width() const;
		int get_screen_height() const;

		void set_fullscreen(bool fullscreen_enabled);
		bool is_fullscreen() const;
	};
}

#endif
