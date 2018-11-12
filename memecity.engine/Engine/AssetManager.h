#ifndef _ASSET_MANAGER_H
#define _ASSET_MANAGER_H
#include <map>
#include "SDL\GraphicsFacade.h"
#include "SDL\Wrappers\RawTextureWrapper.h"
#include "SDL\Wrappers\RawMusicWrapper.h"
#include "SDL\Wrappers\RawSfxWrapper.h"
#include "SDL\Wrappers\RawFontWrapper.h"

namespace memecity::engine {
	class AssetManager
	{
	private:
		sdl::GraphicsFacade& graphics_facade;

		const std::string base_path = SDL_GetBasePath();
		std::map<std::string, std::unique_ptr<sdl::RawTextureWrapper>> textures;
		std::map<std::string, std::unique_ptr<sdl::RawTextureWrapper>> texts;
		std::map<std::string, std::unique_ptr<sdl::RawFontWrapper>> fonts;
		std::map<std::string, std::unique_ptr<sdl::RawMusicWrapper>> music;
		std::map<std::string, std::unique_ptr<sdl::RawSfxWrapper>> sfx;

		sdl::RawFontWrapper& get_font(std::string filename, int size);

	public:
		AssetManager(sdl::GraphicsFacade& graphics_facade);
		~AssetManager();

		const sdl::RawTextureWrapper& get_texture(std::string filename);
		const sdl::RawTextureWrapper&  get_text(std::string text, std::string filename, int size, SDL_Color color);
		const sdl::RawMusicWrapper& get_music(std::string filename);
		const sdl::RawSfxWrapper& get_sfx(std::string filename);
	};
}

#endif
