#include "MultimediaManager.h"

MultimediaManager::MultimediaManager(bool is_fullscreen)
{
	graphics_facade = std::make_shared<GraphicsFacade>(is_fullscreen);
	asset_manager = std::make_unique<AssetManager>(graphics_facade);
	audio_facade = std::make_unique<AudioFacade>();
}

bool MultimediaManager::init() const
{	
	if (graphics_facade->Init())
	{
		audio_facade->Init();
		audio_facade->OpenAudio(44100, 2, 4096);
		return true;
	}

	return false;
}

void MultimediaManager::play_background_music(std::string name, int volume) const
{
	const auto music = asset_manager->get_music(name);
	audio_facade->PlayBackgroundMusic(music, volume);
}

void MultimediaManager::play_sound_effect(std::string name, int repeats, int volume, int channel) const
{
	const auto sound = asset_manager->get_sfx(name);
	audio_facade->PlaySoundEffect(sound, repeats, volume, channel);
}

void MultimediaManager::pause_background_music() const
{	
	audio_facade->PauseBackgroundMusic();
}

void MultimediaManager::clear_graphics() const
{
	graphics_facade->Clear();
}

void MultimediaManager::render_graphics() const
{
	graphics_facade->Render();
}

std::shared_ptr<Texture> MultimediaManager::get_texture(std::string filename)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_texture(filename));
}

std::shared_ptr<Texture> MultimediaManager::get_texture(std::string filename, int x, int y, int width, int height)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_texture(filename), x, y, width, height);
}

std::shared_ptr<Texture> MultimediaManager::get_text_texture(std::string text, std::string font_path, int size, SDL_Color color)
{
	return std::make_shared<Texture>(graphics_facade, asset_manager->get_text(text, font_path, size, color));
}






