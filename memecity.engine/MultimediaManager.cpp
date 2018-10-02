#include "MultimediaManager.h"

MultimediaManager::MultimediaManager()
{
	graphics_facade = std::make_shared<GraphicsFacade>();
	asset_manager = std::make_unique<AssetManager>(graphics_facade);
	audio_facade = std::make_unique<AudioFacade>();
}

bool MultimediaManager::Init() const
{	
	if (graphics_facade->Init())
	{
		audio_facade->Init();
		audio_facade->OpenAudio(44100, 2, 4096);
		return true;
	}

	return false;
}

void MultimediaManager::PlayBackgroundMusic(std::string name) const
{
	const auto music = asset_manager->GetMusic(name);
	audio_facade->PlayBackgroundMusic(music, 50);
}

void MultimediaManager::PlaySoundEffect(std::string name, int repeats, int volume, int channel) const
{
	const auto sound = asset_manager->GetSFX(name);
	audio_facade->PlaySoundEffect(sound, repeats, volume, channel);
}

void MultimediaManager::PauseBackgroundMusic() const
{	
	audio_facade->PauseBackgroundMusic();
}

void MultimediaManager::ClearGraphics() const
{
	graphics_facade->Clear();
}

void MultimediaManager::RenderGraphics() const
{
	graphics_facade->Render();
}

void MultimediaManager::DrawTexture(SDL_Texture* texture, SDL_Rect* sdl_rect, SDL_Rect* render_rect) const
{
	graphics_facade->DrawTexture(texture, sdl_rect, render_rect);
}

SDL_Texture* MultimediaManager::GetText(const std::string& cs, const std::string& font_path, const int size, const SDL_Color& color) const
{
	return asset_manager->GetText(cs, font_path, size, color);
}

SDL_Texture* MultimediaManager::GetTexture(const std::string& cs) const
{
	return asset_manager->GetTexture(cs);
}



