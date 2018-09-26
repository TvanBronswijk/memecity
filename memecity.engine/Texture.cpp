#include "Texture.h"

Texture::Texture(std::string filename)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(filename);

	SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::Texture(std::string filename, int x, int y, int width, int height)
{
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(filename);

	mClipped = true;

	mWidth = width;
	mHeight = height;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClippedRect.x = x;
	mClippedRect.y = y;
	mClippedRect.w = mWidth;
	mClippedRect.h = mHeight;
}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color color)
{
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, color);

	mClipped = false;

	SDL_QueryTexture(mTex, nullptr, nullptr, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::~Texture()
{
	mTex = nullptr;
	mGraphics = nullptr;
}

void Texture::Render()
{
	Vector2 pos = Pos(world);
	mRenderRect.x = int(pos.x - mWidth * 0.5f);
	mRenderRect.y = int(pos.y - mHeight * 0.5f);

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClippedRect : nullptr, &mRenderRect);
}