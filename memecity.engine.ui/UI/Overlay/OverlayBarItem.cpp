#include "OverlayBarItem.h"

void memecity::engine::ui::overlay::OverlayBarItem::render()
{
	multimedia_manager->render_rect(x, y, width, 10, true, background);
	multimedia_manager->render_rect(x, y, width/max*value, 10, true, forground);
}
