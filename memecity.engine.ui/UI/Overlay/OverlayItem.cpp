#include "OverlayItem.h"

namespace memecity::engine::ui::overlay
{

	void OverlayItem::render() const
	{
		auto texture = multimedia_manager.get_text_texture(text, "Fonts/Minecraftia-Regular.ttf", size, { 255,255,255 });
		texture->set_position(Vector2{ x,y });
		multimedia_manager.render_texture(*texture);
	}
}
