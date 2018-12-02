#include "OverlayItem.h"

namespace memecity::engine::ui::overlay
{

	void OverlayItem::render() const
	{
		auto texture = multimedia_manager.get_text(text, size);
		texture->set_position(Vector2{ x,y });
		multimedia_manager.render_text(*texture);
	}
}
