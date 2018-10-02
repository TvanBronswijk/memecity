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
	const auto music = asset_manager->GetMusic(name);
	audio_facade->PlayBackgroundMusic(music, volume);
}

void MultimediaManager::play_sound_effect(std::string name, int repeats, int volume, int channel) const
{
	const auto sound = asset_manager->GetSFX(name);
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

void MultimediaManager::draw_texture(SDL_Texture* texture, SDL_Rect* sdl_rect, SDL_Rect* render_rect) const
{
	graphics_facade->DrawTexture(texture, sdl_rect, render_rect);
}

SDL_Texture* MultimediaManager::get_text(const std::string& cs, const std::string& font_path, const int size, const SDL_Color& color) const
{
	return asset_manager->GetText(cs, font_path, size, color);
}

SDL_Texture* MultimediaManager::get_texture(const std::string& cs) const
{
	return asset_manager->GetTexture(cs);
}



