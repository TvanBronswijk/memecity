#include "AssetManager.h"
#include "GraphicsFacade.h"

AssetManager::AssetManager(std::shared_ptr<GraphicsFacade> graphics)
{
	graphics_facade = graphics;
}

AssetManager::~AssetManager()
{
	for (const auto texture : textures)
	{
		if (texture.second != nullptr)
		{
			SDL_DestroyTexture(texture.second);
		}
	}
	textures.clear();

	for (const auto text : texts)
	{
		if (text.second != nullptr)
		{
			SDL_DestroyTexture(text.second);
		}
	}
	texts.clear();

	for (const auto font : fonts)
	{
		if (font.second != nullptr)
		{
			TTF_CloseFont(font.second);
		}
	}
	fonts.clear();
}

SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (textures[fullPath] == nullptr)
		textures[fullPath] = graphics_facade->LoadTexture(fullPath);

	return textures[fullPath];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(filename, size);
	std::string key = text + filename + char(size) + char(color.r) + char(color.g) + char(color.b);

	if (texts[key] == nullptr)
		texts[key] = graphics_facade->LoadTextTexture(font, text, color);

	return texts[key];
}


TTF_Font* AssetManager::GetFont(std::string filename, int size)
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

Mix_Music* AssetManager::GetMusic(std::string filename)
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

Mix_Chunk* AssetManager::GetSFX(std::string filename)
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
