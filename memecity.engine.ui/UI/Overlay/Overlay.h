#ifndef _OVERLAY_H
#define  _OVERLAY_H

#include <memory>
#include "OverlayItem.h"
#include "Engine/MultimediaManager.h"
#include "OverlayTextItem.h"
#include "OverlayBarItem.h"

namespace memecity::engine::ui::overlay {
	class Overlay
	{
	private:
		std::map < std::string, std::unique_ptr<OverlayTextItem>> overlay_text_items;
		std::map < std::string, std::unique_ptr<OverlayBarItem>> overlay_bar_items;
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
			if (overlay_text_items.find(name) != overlay_text_items.end()) {
				overlay_text_items[name]->update(text);
			}
		}

		void update(std::string name, int value)
		{
			if (overlay_bar_items.find(name) != overlay_bar_items.end()) {
				overlay_bar_items[name]->update(value);
			}
		}

		template<class... Args>
		OverlayTextItem& create_overlay_text_item(std::string name,Args&&... args)
		{
			static_assert(std::is_constructible<OverlayTextItem, MultimediaManager&, Overlay&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			overlay_text_items.insert_or_assign(name, (std::make_unique<OverlayTextItem>(multimedia_manager, *this, std::forward<Args>(args)...)));
			return *overlay_text_items[name];

		}

		template<class... Args>
		OverlayBarItem& create_overlay_bar_item(std::string name, Args&&... args)
		{
			static_assert(std::is_constructible<OverlayBarItem, MultimediaManager&, Overlay&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			overlay_bar_items.insert_or_assign(name, (std::make_unique<OverlayBarItem>(multimedia_manager, *this, std::forward<Args>(args)...)));
			return *overlay_bar_items[name];

		}

		void render();

	};
}

#endif