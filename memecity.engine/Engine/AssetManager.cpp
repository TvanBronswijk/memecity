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
		std::string full_path = base_path;
		full_path.append("Assets/" + filename);

		if (textures.find(full_path) == textures.end())
		{
			textures[full_path] = graphics_facade->load_texture(full_path);
		}

		return *textures[full_path];
	}

	///<summary>Returns a text texture based on a given text and filename.</summary>
	const sdl::RawTextureWrapper&  AssetManager::get_text(std::string text, std::string font, int size, SDL_Color color)
	{
		auto& raw_font = get_font(font, size);
		std::string key = text + font + char(size) + char(color.r) + char(color.g) + char(color.b);
		if (texts.find(key) == texts.end())
		{
			texts[key] = graphics_facade->load_text_texture(raw_font, text, color);
		}
		return *texts[key];
	}

	///<summary>Returns a font based on a given filename.</summary>
	const sdl::RawFontWrapper& AssetManager::get_font(std::string filename, int size)
	{
		std::string full_path = base_path;
		full_path.append("Assets/" + filename);
		const std::string key = full_path + char(size);
		if (fonts.find(key) == fonts.end())
		{
			fonts[key] = graphics_facade->load_font(full_path, size);
		}
		return *fonts[key];
	}
	///<summary>Returns music based on a given filename.</summary>
	const sdl::RawMusicWrapper& AssetManager::get_music(std::string filename)
	{
		std::string full_path = base_path;
		full_path.append("Assets/" + filename);

		if (music.find(full_path) == music.end())
		{
			music[full_path] = audio_facade->load_music(full_path);
		}

		return *music[full_path];
	}

	///<summary>Returns a sound effect based on a given filename.</summary>
	const sdl::RawSfxWrapper& AssetManager::get_sfx(std::string filename)
	{
		std::string full_path = base_path;
		full_path.append("Assets/" + filename);

		if (sfx.find(full_path) == sfx.end())
		{
			sfx[full_path] = audio_facade->load_sfx(full_path);
		}
		return *sfx[full_path];
	}
}
