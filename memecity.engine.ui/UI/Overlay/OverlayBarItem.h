#pragma once
#include "OverlayItem.h"

class OverlayBarItem : public memecity::engine::ui::overlay::OverlayItem<int>
{
private:
	int value;
public:
	OverlayBarItem(memecity::engine::MultimediaManager& multimedia_manager,
		memecity::engine::ui::overlay::Overlay& parent, int value, int size, float x, float y)
		: OverlayItem<int>(multimedia_manager, parent, value, size, x, y), value(value)
	{
	}

	void update(int value) override { this->value = value; };
	void render() override;
};
