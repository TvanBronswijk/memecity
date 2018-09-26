#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "Graphic.h"
#include <SDL.h>
#include "AssetManager.h"

class Texture : public Graphic
{
protected:

	SDL_Texture* mTex;

	Graphics* mGraphics;

	int mWidth;
	int mHeight;

	bool mClipped;
	SDL_Rect mRenderRect;
	SDL_Rect mClippedRect;
public:

	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int width, int height);
	Texture(std::string text, std::string fontPath, int size, SDL_Color color);
	~Texture();

	virtual void Render();
};

#endif