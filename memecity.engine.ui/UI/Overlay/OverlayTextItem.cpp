#include "OverlayTextItem.h"

void OverlayTextItem::render()
{
	multimedia_manager->render_text(x, y, value, size);
}

