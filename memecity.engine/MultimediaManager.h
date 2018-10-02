#ifndef _MULTIMEDIAMANAGER_H
#define _MULTIMEDIAMANAGER_H

#include "AssetManager.h"
#include "AudioFacade.h"

class MultimediaManager
{
	private:
		std::unique_ptr<AssetManager> asset_manager;
		std::unique_ptr<AudioFacade> audio_facade;
		std::shared_ptr<GraphicsFacade> graphics_facade;

	public:
		MultimediaManager(bool is_fullscreen);
		bool init() const;

		void play_background_music(std::string name, int volume) const;
		void play_sound_effect(std::string name, int repeats, int volume, int channel) const;
		void pause_background_music() const;

		void clear_graphics() const;
		void render_graphics() const;
		void draw_texture(SDL_Texture* texture, SDL_Rect* sdl_rect, SDL_Rect* render_rect) const;
		
		SDL_Texture* get_text(const std::string& cs, const std::string& font_path, const int size, const SDL_Color& color) const;
		SDL_Texture* get_texture(const std::string& cs) const;
};

#endif