#include "AssetManager.h"
#include "GraphicsFacade.h"

/**
 * Constructor which assigns a given graphics_facade to it's member variable
 */
AssetManager::AssetManager(std::shared_ptr<GraphicsFacade> graphics_facade)
{
	this->graphics_facade = graphics_facade;
}

/**
 * Cleanup
 */
AssetManager::~AssetManager()
{
	for (auto texture : textures)
	{
		if (texture.second != nullptr)
		{
			SDL_DestroyTexture(texture.second);
		}
	}
	textures.clear();

	for (auto text : texts)
	{
		if (text.second != nullptr)
		{
			SDL_DestroyTexture(text.second);
		}
	}
	texts.clear();

	for (auto font : fonts)
	{
		if (font.second != nullptr)
		{
			TTF_CloseFont(font.second);
		}
	}
	fonts.clear();
}

/**
 * Returns a texture based on given filename
 */
SDL_Texture* AssetManager::get_texture(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (textures[fullPath] == nullptr)
	{
		textures[fullPath] = graphics_facade->load_texture(fullPath);
	}

	return textures[fullPath];
}

/**
 * Returns a text texture based on a given text and filename
 */
SDL_Texture* AssetManager::get_text(std::string text, std::string filename, int size, SDL_Color color)
{
	TTF_Font* font = get_font(filename, size);
	std::string key = text + filename + char(size) + char(color.r) + char(color.g) + char(color.b);

	if (texts[key] == nullptr)
	{
		texts[key] = graphics_facade->load_text_texture(font, text, color);
	}

	return texts[key];
}

/**
 * Returns a font based on a given filename
 */
TTF_Font* AssetManager::get_font(std::string filename, int size)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);
	const std::string key = fullPath + char(size);

	if (fonts[key] == nullptr)
	{
		fonts[key] = TTF_OpenFont(fullPath.c_str(), size);

		if (fonts[key] == nullptr)
		{
			printf("Font loading error: Font-%s Error-%s\n", filename.c_str(), TTF_GetError());
		}
	}

	return fonts[key];
}

/**
 * Returns music based on a given filename
 */
Mix_Music* AssetManager::get_music(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (music[fullPath] == nullptr)
	{
		music[fullPath] = Mix_LoadMUS(fullPath.c_str());

		if (music[fullPath] == nullptr)
		{
			printf("Music loading error: file- %s Error- %s", filename.c_str(), Mix_GetError());
		}
	}

	return music[fullPath];
}

/**
 * Returns a sound effect based on a given filename
 */
Mix_Chunk* AssetManager::get_sfx(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (sfx[fullPath] == nullptr)
	{
		sfx[fullPath] = Mix_LoadWAV(fullPath.c_str());
		if (sfx[fullPath] == nullptr)
		{
			printf("SFX loading error: file-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}

	return sfx[fullPath];
}