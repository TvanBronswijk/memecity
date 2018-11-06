#ifndef _MULTIMEDIAMANAGER_H
#define _MULTIMEDIAMANAGER_H

#include "AnimatedTexture.h"
#include "AssetManager.h"
#include "AudioFacade.h"
#include "Texture.h"
#include "Color.h"

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

	std::shared_ptr<Texture> get_texture(std::string filename);
	std::shared_ptr<Texture> get_texture(std::string filename, int x, int y, int width, int height);
	std::shared_ptr<AnimatedTexture> get_animated_texture(TimerFacade *timer, std::string filename, int x, int y, int width, int height, int frame_count, float animation_speed, AnimatedTexture::AnimationDirection direction);
	std::shared_ptr<Texture> get_text_texture(std::string text, std::string font_path, int size, Color color);

	int get_screen_width();
	int get_screen_height();
};

#endif