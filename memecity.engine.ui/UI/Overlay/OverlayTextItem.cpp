#include "OverlayTextItem.h"

void memecity::engine::ui::overlay::OverlayTextItem::render()
{
	multimedia_manager->render_text(x, y, value, size);
}

