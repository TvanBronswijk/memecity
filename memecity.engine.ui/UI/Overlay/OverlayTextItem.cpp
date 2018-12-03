#include "OverlayTextItem.h"

void OverlayTextItem::render()
{
	auto texture = multimedia_manager.get_text(value, size);
	texture->set_position(Vector2{ x,y });
	multimedia_manager.render_text(*texture);
}

