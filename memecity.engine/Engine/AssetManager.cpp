#include "AssetManager.h"

namespace memecity::engine {
	///<summary>Cleanup.</summary>
	AssetManager::~AssetManager()
	{
		textures.clear();
		texts.clear();
		fonts.clear();
		music.clear();
		sfx.clear();
	}

	///<summary>Returns a texture based on given filename.</summary>
	const sdl::RawTextureWrapper& AssetManager::get_texture(std::string filename)
	{
		std::string fullPath = base_path;
		fullPath.append("Assets/" + filename);

		if (textures.find(fullPath) == textures.end())
		{
			textures[fullPath] = graphics_facade->load_texture(fullPath);
		}

		return *textures[fullPath];
	}

	///<summary>Returns a text texture based on a given text and filename.</summary>
	const sdl::RawTextureWrapper&  AssetManager::get_text(std::string text, std::string filename, int size, SDL_Color color)
	{
		auto& font = get_font(filename, size);
		std::string key = text + filename + char(size) + char(color.r) + char(color.g) + char(color.b);

		if (texts.find(key) == texts.end())
		{
			texts[key] = graphics_facade->load_text_texture(font, text, color);
		}

		return *texts[key];
	}

	///<summary>Returns a font based on a given filename.</summary>
	sdl::RawFontWrapper& AssetManager::get_font(std::string filename, int size)
	{
		std::string fullPath = base_path;
		fullPath.append("Assets/" + filename);
		const std::string key = fullPath + char(size);

		if (fonts[key] == nullptr)
		{
			fonts[key] = std::make_unique<sdl::RawFontWrapper>(TTF_OpenFont(fullPath.c_str(), size));

			if (fonts[key] == nullptr)
			{
				printf("Font loading error: Font-%s Error-%s\n", filename.c_str(), TTF_GetError());
			}
		}

		return *fonts[key];
	}
	///<summary>Returns music based on a given filename.</summary>
	const sdl::RawMusicWrapper& AssetManager::get_music(std::string filename)
	{
		std::string fullPath = base_path;
		fullPath.append("Assets/" + filename);

		if (music[fullPath] == nullptr)
		{
			music[fullPath] = std::make_unique<sdl::RawMusicWrapper>(Mix_LoadMUS(fullPath.c_str()));

			if (music[fullPath] == nullptr)
			{
				printf("Music loading error: file- %s Error- %s", filename.c_str(), Mix_GetError());
			}
		}

		return *music[fullPath];
	}

	///<summary>Returns a sound effect based on a given filename.</summary>
	const sdl::RawSfxWrapper& AssetManager::get_sfx(std::string filename)
	{
		std::string fullPath = base_path;
		fullPath.append("Assets/" + filename);

		if (sfx[fullPath] == nullptr)
		{
			sfx[fullPath] = std::make_unique<sdl::RawSfxWrapper>(Mix_LoadWAV(fullPath.c_str()));
			if (sfx[fullPath] == nullptr)
			{
				printf("SFX loading error: file-%s Error-%s", filename.c_str(), Mix_GetError());
			}
		}

		return *sfx[fullPath];
	}
}
