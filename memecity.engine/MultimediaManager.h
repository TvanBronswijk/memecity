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
		MultimediaManager();
		bool Init() const;

		void PlayBackgroundMusic(std::string name, int volume) const;
		void PlaySoundEffect(std::string name, int repeats, int volume, int channel) const;
		void PauseBackgroundMusic() const;

		void ClearGraphics() const;
		void RenderGraphics() const;
		void DrawTexture(SDL_Texture* texture, SDL_Rect* sdl_rect, SDL_Rect* render_rect) const;
		
		SDL_Texture* GetText(const std::string& cs, const std::string& font_path, const int size, const SDL_Color& color) const;
		SDL_Texture* GetTexture(const std::string& cs) const;
};

#endif