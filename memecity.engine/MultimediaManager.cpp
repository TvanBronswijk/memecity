#include "MultimediaManager.h"

MultimediaManager::MultimediaManager(bool is_fullscreen)
{
	graphics_facade = std::make_shared<GraphicsFacade>(is_fullscreen);
	asset_manager = std::make_unique<AssetManager>(graphics_facade);
	audio_facade = std::make_unique<AudioFacade>();
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
	const auto music = asset_manager->get_music(name);
	audio_facade->play_background_music(music, volume);
}

void MultimediaManager::play_sound_effect(std::string const name, int const repeats, int const volume, int const channel) const
{
	const auto sound = asset_manager->get_sfx(name);
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

void MultimediaManager::render_graphics() const
{
	graphics_facade->render();
}

std::shared_ptr<Texture> MultimediaManager::get_texture(const std::string filename)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_texture(filename));
}

std::shared_ptr<Texture> MultimediaManager::get_texture(std::string const filename, int x, int y, int width, int height)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_texture(filename), x, y, width, height);
}

std::shared_ptr<AnimatedCharacter> MultimediaManager::get_animated_texture(TimerFacade *timer, std::string filename, int x, int y, int width, int height, int frame_count, float animation_speed, AnimatedCharacter::ANIMATION_DIRECTION direction)
{
	auto texture = asset_manager->get_texture(filename);
	return std::make_shared<AnimatedCharacter>(timer, graphics_facade, texture, x, y, width, height, frame_count, animation_speed, direction);
}

std::shared_ptr<Texture> MultimediaManager::get_text_texture(std::string const text, std::string const font_path, const int size, Color color)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_text(text, font_path, size, color.get_sdl_color()));
}