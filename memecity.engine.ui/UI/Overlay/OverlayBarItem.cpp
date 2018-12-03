#include "OverlayBarItem.h"

void OverlayBarItem::render()
{
	multimedia_manager->render_rect(x, y, 100*2, 10, true, { 255,0,0 });
	multimedia_manager->render_rect(x, y, value*2, 10, true, { 0,255,0 });
}
