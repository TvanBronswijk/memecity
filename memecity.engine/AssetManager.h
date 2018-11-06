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

	const std::string base_path = SDL_GetBasePath();
	std::map<std::string, SDL_Texture*> textures;
	std::map<std::string, SDL_Texture*> texts;
	std::map<std::string, TTF_Font*> fonts;
	std::map<std::string, Mix_Music*> music;
	std::map<std::string, Mix_Chunk*> sfx;

	TTF_Font* get_font(std::string filename, int size);

public:
	AssetManager(std::shared_ptr<GraphicsFacade> graphics_facade);
	~AssetManager();

	SDL_Texture* get_texture(std::string filename);
	SDL_Texture* get_text(std::string text, std::string filename, int size, SDL_Color color);
	Mix_Music* get_music(std::string filename);
	Mix_Chunk* get_sfx(std::string filename);
};

#endif