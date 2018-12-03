﻿#pragma once
#include "OverlayItem.h"

class OverlayTextItem: public memecity::engine::ui::overlay::OverlayItem<std::string>
{
public:


	OverlayTextItem(memecity::engine::MultimediaManager& multimedia_manager,memecity::engine::ui::overlay::Overlay& parent, std::string text, int size, float x, float y)
		: OverlayItem(multimedia_manager, parent, text, size, x, y)
	{
	}

	void render() override;
	void update(std::string new_value) override { value = new_value; };
};
