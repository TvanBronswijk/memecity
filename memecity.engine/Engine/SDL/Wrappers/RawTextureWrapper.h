#ifndef _RAW_TEXTURE_WRAPPER_H
#define _RAW_TEXTURE_WRAPPER_H
#include <SDL.h>

namespace memecity::engine::sdl {
	class RawTextureWrapper
	{
	private:
		SDL_Texture* texture;

	public:
		RawTextureWrapper()
			: texture(nullptr) {}

		RawTextureWrapper(SDL_Texture* tex)
			: texture(tex) {}

		~RawTextureWrapper()
		{
			SDL_DestroyTexture(texture);
		}
		SDL_Texture* get() const
		{
			return texture;
		}
		SDL_Texture* operator->() const
		{
			return texture;
		}
		SDL_Texture* operator*()  const
		{
			return texture;
		}
	};
}

#endif

