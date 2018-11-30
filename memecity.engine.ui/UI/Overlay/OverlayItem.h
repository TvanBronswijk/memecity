#ifndef _OVERLAY_ITEM_H
#define  _OVERLAY_ITEM_H
#include <vector>
#include "Engine/Textures/TextTexture.h"
#include "Engine/MultimediaManager.h"


namespace memecity::engine::ui::overlay {
	class Overlay;
	class OverlayItem
	{
	private:
		float x;
		float y;
		int size;
		std::string text;
		Overlay& parent;
		MultimediaManager& multimedia_manager;
	public:
		OverlayItem(MultimediaManager& multimedia_manager, Overlay& parent, std::string text, int size, float x, float y)
		:x(x), y(y),size(size), text(text), parent(parent), multimedia_manager(multimedia_manager){}

		void update(std::string newtext)
		{
			this->text = newtext;
		}

		//texture::TextTexture& get_texture() const;
		void render() const;

	};
}

#endif