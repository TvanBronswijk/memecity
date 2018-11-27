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
		std::vector<std::unique_ptr<OverlayItem>> overlay_items;
		MultimediaManager& multimedia_manager;
		std::unique_ptr<texture::Texture> background_texture;
		float x;
		float y;
	public:
		Overlay(MultimediaManager& multimedia_manager, std::unique_ptr<texture::Texture> background_texture, float x, float y)
		:multimedia_manager(multimedia_manager),background_texture(std::move(background_texture)),x(x),y(y)
		{
		}

		template<class... Args>
		OverlayItem& create_overlay_item(Args&&... args)
		{
			static_assert(std::is_constructible<OverlayItem, MultimediaManager&, Overlay&, Args...>::value, "The requested type cannot be constructed from the arguments provided.");
			return *overlay_items.emplace_back(std::make_unique<OverlayItem>(multimedia_manager, *this, std::forward<Args>(args)...));

		}

		void render();

	};
}

#endif