#ifndef _OVERLAY_H
#define  _OVERLAY_H

#include <memory>
#include "OverlayItem.h"
#include "Engine/MultimediaManager.h"
#include "OverlayTextItem.h"
#include "OverlayBarItem.h"
#include <unordered_map>

namespace memecity::engine::ui::overlay {
	class Overlay
	{
	private:
		std::unordered_map<std::string, std::unique_ptr<OverlayTextItem>> overlay_text_items;
		std::unordered_map < std::string, std::unique_ptr<OverlayBarItem>> overlay_bar_items;
		MultimediaManager* multimedia_manager;
		std::unique_ptr<texture::Texture> background_texture;
		float x;
		float y;
	public:
		Overlay(MultimediaManager& multimedia_manager, std::unique_ptr<texture::Texture> background_texture, float x, float y)
		:multimedia_manager(&multimedia_manager),background_texture(std::move(background_texture)),x(x),y(y)
		{
			this->background_texture->set_position(Vector2{ this->background_texture->get_clipped_rect().w * 0.5f,  this->background_texture->get_clipped_rect().h * 0.5f });

		}

		void update(std::string name, std::string text)
		{
			auto result = overlay_text_items.find(name);
			if (result != overlay_text_items.end()) {
				result->second->update(text);
			}
		}

		void update(std::string name, int value)
		{
			auto result = overlay_bar_items.find(name);
			if (result != overlay_bar_items.end()) {
				result->second->update(value);
			}
		}

		template<class... Args>
		OverlayTextItem& create_overlay_text_item(std::string name,Args&&... args)
		{
			static_assert(std::is_constructible<OverlayTextItem, MultimediaManager&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			overlay_text_items.insert_or_assign(name, (std::make_unique<OverlayTextItem>(*multimedia_manager, std::forward<Args>(args)...)));
			return *overlay_text_items[name];

		}

		template<class... Args>
		OverlayBarItem& create_overlay_bar_item(std::string name, Args&&... args)
		{
			static_assert(std::is_constructible<OverlayBarItem, MultimediaManager&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			overlay_bar_items.insert_or_assign(name, (std::make_unique<OverlayBarItem>(*multimedia_manager, std::forward<Args>(args)...)));
			return *overlay_bar_items[name];

		}

		void render();

	};
}

#endif