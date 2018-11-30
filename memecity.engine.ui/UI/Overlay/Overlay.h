#ifndef _OVERLAY_H
#define  _OVERLAY_H
#include <vector>
#include <memory>
#include "OverlayItem.h"
#include "Engine/MultimediaManager.h"

namespace memecity::engine::ui::overlay {
	class Overlay
	{
	private:
		std::map<std::string, std::unique_ptr<OverlayItem>> overlay_items;
		MultimediaManager& multimedia_manager;
		std::unique_ptr<texture::Texture> background_texture;
		float x;
		float y;
	public:
		Overlay(MultimediaManager& multimedia_manager, std::unique_ptr<texture::Texture> background_texture, float x, float y)
		:multimedia_manager(multimedia_manager),background_texture(std::move(background_texture)),x(x),y(y)
		{
		}

		void update(std::string name, std::string text)
		{
			if (overlay_items.find(name) != overlay_items.end()) {
				overlay_items[name]->update(text);
			}
		}

		template<class... Args>
		OverlayItem& create_overlay_item(std::string name,Args&&... args)
		{
			static_assert(std::is_constructible<OverlayItem, MultimediaManager&, Overlay&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			overlay_items.insert_or_assign(name, (std::make_unique<OverlayItem>(multimedia_manager, *this, std::forward<Args>(args)...)));
			return *overlay_items[name];

		}

		void render();

	};
}

#endif