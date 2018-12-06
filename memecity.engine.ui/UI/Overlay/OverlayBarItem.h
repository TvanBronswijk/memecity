#ifndef OVERLAYBARITEM_H
#define OVERLAYBARITEM_H
#include "OverlayItem.h"

namespace memecity::engine::ui::overlay {
	class OverlayBarItem : public OverlayItem<int>
	{
	private:
		int max;
		int width;
		sdl::Color background;
		sdl::Color forground;

	public:
		OverlayBarItem(MultimediaManager& multimedia_manager,
			 int value, int size, float x, float y, int max, int width, sdl::Color background = sdl::Color(100, 100, 100), sdl::Color forground = sdl::Color(200, 200, 200)) :max(max), width(width), background(background), forground(forground)
			, OverlayItem<int>(multimedia_manager, value, size, x, y)
		{
		}

		void render() override;
	};
}
#endif // OVERLAYBARITEM_H
