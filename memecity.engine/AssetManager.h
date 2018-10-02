#ifndef _ASSET_MANAGER_H
#define _ASSET_MANAGER_H
#include <map>
#include <SDL.h>
#include <SDL_mixer.h>
#include "GraphicsFacade.h"

class AssetManager
{
	private:
		std::shared_ptr<GraphicsFacade> graphics_facade;

		std::map<std::string, SDL_Texture*> textures;
		std::map<std::string, SDL_Texture*> texts;
		std::map<std::string, TTF_Font*> fonts;
		std::map<std::string, Mix_Music*> music;
		std::map<std::string, Mix_Chunk*> sfx;

		TTF_Font* GetFont(std::string filename, int size);

	public:

		AssetManager(std::shared_ptr<GraphicsFacade> graphicsFacade);
		SDL_Texture* GetTexture(std::string filename);
		SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color);
		Mix_Music* GetMusic(std::string filename);
		Mix_Chunk* GetSFX(std::string filename);

		~AssetManager();
};

#endif