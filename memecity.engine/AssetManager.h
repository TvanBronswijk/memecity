#ifndef _ASSET_MANAGER_H
#define _ASSET_MANAGER_H
#include <map>
#include <SDL.h>
#include "RawTextureWrapper.h"
#include "RawMusicWrapper.h"
#include "RawSfxWrapper.h"
#include "RawFontWrapper.h"
#include "GraphicsFacade.h"

class AssetManager
{
private:
	GraphicsFacade& graphics_facade;

	const std::string base_path = SDL_GetBasePath();
	std::map<std::string, std::unique_ptr<RawTextureWrapper>> textures;
	std::map<std::string, std::unique_ptr<RawTextureWrapper>> texts;
	std::map<std::string, std::unique_ptr<RawFontWrapper>> fonts;
	std::map<std::string, std::unique_ptr<RawMusicWrapper>> music;
	std::map<std::string, std::unique_ptr<RawSfxWrapper>> sfx;

	RawFontWrapper& get_font(std::string filename, int size);

public:
	AssetManager(GraphicsFacade& graphics_facade);
	~AssetManager();

	const RawTextureWrapper& get_texture(std::string filename);
	const RawTextureWrapper&  get_text(std::string text, std::string filename, int size, SDL_Color color);
	const RawMusicWrapper& get_music(std::string filename);
	const RawSfxWrapper& get_sfx(std::string filename);
};

#endif