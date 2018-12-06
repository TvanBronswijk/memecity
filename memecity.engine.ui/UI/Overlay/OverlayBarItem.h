#ifndef OVERLAYBARITEM_H
#define OVERLAYBARITEM_H
#include "OverlayItem.h"

class OverlayBarItem : public memecity::engine::ui::overlay::OverlayItem<int>
{
private:
	int max;
	int width;
	memecity::engine::sdl::Color background;
	memecity::engine::sdl::Color forground;

public:
	OverlayBarItem(memecity::engine::MultimediaManager& multimedia_manager,
		memecity::engine::ui::overlay::Overlay& parent, int value, int size, float x, float y, int max,int width, memecity::engine::sdl::Color background = memecity::engine::sdl::Color(100,100,100), memecity::engine::sdl::Color forground = memecity::engine::sdl::Color(200, 200, 200)):max(max),width(width),background(background),forground(forground)
		, OverlayItem<int>(multimedia_manager, parent, value, size, x, y)
	{
	}

	void render() override;
};
#endif // OVERLAYBARITEM_H
